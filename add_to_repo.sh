#!/bin/bash

set -euxo pipefail

readonly GITHUB_REPO_SSH=$1
git clone $GITHUB_REPO_SSH

DIR="$(basename $GITHUB_REPO_SSH .git)"

echo "Removing .git from cloned repo..."
rm -rf $DIR/.git

echo "Adding to new repo..."
git add $DIR && git commit -m "Add to main repo." && git push origin main

set +x
