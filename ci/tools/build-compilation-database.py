#!/usr/bin/env python3

import json
import os
import re
import subprocess
import sys


_UNKNOWN_ARGUMENTS = [
    '-fno-canonical-system-headers'
]


def _bazel_info(key):
    return subprocess.check_output(args=['bazel', 'info', key], universal_newlines=True).strip()


def _get_compile_command_files(dump_command_command_action_root):
    compile_command_file_regex = re.compile(r'compile-command-.*\.json')

    for path, dir_names, file_names in os.walk(dump_command_command_action_root):
        if path == dump_command_command_action_root:
            try:
                dir_names.remove('external')
            except ValueError:
                pass

        for file_name in file_names:
            if compile_command_file_regex.fullmatch(file_name):
                yield os.path.join(path, file_name)


def _load_compile_command_file(file_path):
    with open(file_path) as f:
        return json.load(f)


def _sanitize_compile_command(compile_command, execution_root):
    compile_command['directory'] = execution_root

    new_arguments = [arg for arg in compile_command['arguments'] if arg not in _UNKNOWN_ARGUMENTS]

    new_arguments.extend(['-Wno-unknown-warning-option'])

    compile_command['arguments'] = new_arguments

    return compile_command


def main():
    execution_root = _bazel_info('execution_root')
    build_root = os.path.dirname(_bazel_info('bazel-bin'))

    dump_command_command_action_root = os.path.join(build_root,
                                                    'extra_actions',
                                                    'ci',
                                                    'dump-cpp-compile-command-action')

    compilation_database = []

    for file_path in _get_compile_command_files(dump_command_command_action_root):
        compile_command = _load_compile_command_file(file_path)

        compilation_database.append(_sanitize_compile_command(compile_command, execution_root))

    json.dump(compilation_database, sys.stdout)


if __name__ == "__main__":
    main()
