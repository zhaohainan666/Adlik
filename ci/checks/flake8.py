#!/usr/bin/env python3

import re
import os
import subprocess


def _get_source_files(root_path):
    file_name_regex = re.compile(r'.*\.py')

    for path, dirs, file_names in os.walk(root_path):
        try:
            dirs.remove('.git')
        except ValueError:
            pass

        for file_name in file_names:
            if file_name_regex.fullmatch(file_name):
                yield os.path.join(path, file_name)


def main():
    working_directory = os.getcwd()
    has_failure = False

    for file_path in _get_source_files(working_directory):
        if subprocess.run(args=['flake8', file_path]).returncode != 0:
            has_failure = True

    if has_failure:
        exit(1)


if __name__ == "__main__":
    main()
