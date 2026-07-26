#!/usr/bin/env python3

import shutil
import subprocess
from typing import Optional
from dataclasses import dataclass
import pipe
from pathlib import Path
import re
import sys
import argparse

PROJECT_ROOT = Path(__file__).resolve().parent
INCLUDE_ROOT = PROJECT_ROOT / "include"


@dataclass
class clang_format_config:
    command: str
    format_file: Path


def main() -> int:

    parser = argparse.ArgumentParser(
        prog="yutool",
        description="Source code preprocessor for Yu Library",
    )

    parser.add_argument(
        "paths",
        nargs="+",
        type=Path,
        help="Files or directories to process.",
    )

    parser.add_argument(
        "-f",
        "--format",
        action="store_true",
        help="Run clang-format after processing.",
    )

    args = parser.parse_args()

    fmt_config: clang_format_config | None = None

    if args.format:
        fmt_config = make_clang_format_config()

    modified: int = 0

    for path in map(Path.absolute, args.paths):
        if path.is_dir():
            for header in path.glob("**/*.hpp") | pipe.select(lambda p: p.absolute()):
                if process_file(header, fmt_config):
                    print(f"updated: {header}")
                    modified += 1

        elif path.is_file():
            if process_file(path, fmt_config):
                print(f"updated: {path}")
                modified += 1

    print(f"{modified} file(s) updated.")

    return 0


def make_clang_format_config() -> clang_format_config | None:
    command = shutil.which("clang-format")

    if command is None:
        print("warning: clang-format not found", file=sys.stderr)
        return None

    style = PROJECT_ROOT / ".clang-format"

    if not style.is_file():
        print(f"{style} not found.", file=sys.stderr)
        return None

    return clang_format_config(command, style)

YUTOOL_RE = re.compile(r"//\s*yutool:\s*(.*)")


def process_file(path: Path, fmt_config: clang_format_config | None) -> bool:
    COMMANDS = {
        "include guard": include_guard,
        "export headers": export_headers,
    }

    original = path.read_text(encoding="utf-8").splitlines()

    result: list[str] = original.copy()

    while any(YUTOOL_RE.match(line) for line in result):
        line_at = 0
        while line_at < len(result):
            line = result[line_at]

            m = YUTOOL_RE.match(line)
            if not m:
                line_at += 1
                continue

            command = m.group(1).strip()

            if not command in COMMANDS:
                line_at += 1
                continue

            process_result: Optional[int] = COMMANDS[command](path, line_at, result)

            if process_result is None:
                print(f"failed at processing {path}, line:{line_at}")
                return False

            if process_result != 0:
                break

            line_at += 1

    result = [line.replace("yutool(processed):", "yutool:") for line in result]

    result_text = "\n".join(result) + "\n"

    if fmt_config is not None:
        try:
            formatted = subprocess.run(
                [fmt_config.command, f"--style=file:{fmt_config.format_file}"],
                input=result_text,
                text=True,
                capture_output=True,
                check=True,
            ).stdout
            result = formatted.splitlines()
        except subprocess.CalledProcessError as e:
            print(f"error: clang-format failed: {path}", file=sys.stderr)
            print(f"exit code: {e.returncode}", file=sys.stderr)
            return False

    changed = result != original

    result_text = "\n".join(result) + "\n"

    if changed:
        path.write_text(result_text, encoding="utf-8")

    return changed


def include_guard(path: Path, line_at: int, content: list[str]) -> Optional[int]:
    try:
        relative = path.relative_to(INCLUDE_ROOT)
    except ValueError:
        return None

    guard = relative.as_posix()
    guard = re.sub(r"[^A-Za-z0-9]", "_", guard)
    guard = re.sub(r"__", "_", guard)
    guard = guard.upper()
    guard += "_"

    def ensure_line(content: list[str], index: int, line: str, directive: str | None = None) -> bool:
        if index >= len(content):
            content.append(line)
            return True

        if directive is not None and content[index].lstrip().startswith(directive):
            if content[index] != line:
                content[index] = line
                return True
            return False

        if content[index] != line:
            content.insert(index, line)
            return True

        return False

    ifndef = f"#ifndef {guard}"
    define = f"#define {guard}"

    processed: int = 0

    current = line_at + 1

    if ensure_line(content, current, ifndef, "#ifndef"):
        processed += 1
    current += 1

    if ensure_line(content, current, define, "#define"):
        processed += 1
    current += 1

    if ensure_line(content, current, ""):
        processed += 1

    removed = 0

    while content and (content[-1] == "" or content[-1] == "#endif"):
        content.pop()
        removed += 1

    content.append("")
    content.append("#endif")

    processed += 2 - removed

    content[line_at] = content[line_at].replace(
        "yutool:",
        "yutool(processed):",
    )

    return processed


INCLUDE_RE = re.compile(r'^\s*#include\s+"[^"]+\.hpp"(?:\s*//.*)?$')


def export_headers(path: Path, line_at: int, content: list[str]) -> int:

    continued_includes = line_at + 1
    while continued_includes < len(content) and INCLUDE_RE.match(content[continued_includes]):
        continued_includes += 1

    del content[line_at + 1 : continued_includes]

    directory = path.with_suffix("")
    headers = sorted(directory.glob("*.hpp"))

    for i, header in enumerate(headers):
        content.insert(line_at + i + 1, f'#include "{path.stem}/{header.name}" // IWYU pragma: export')

    content[line_at] = content[line_at].replace(
        "yutool:",
        "yutool(processed):",
    )

    return len(headers)


if __name__ == "__main__":
    sys.exit(main())
