# Contributing

This project uses focused, reviewable changes.

## Local Checks

See [doc/guides/cmake.md](doc/guides/cmake.md) for a detailed explanation of configure, build, test,
install, presets, and common CMake troubleshooting.

For a new checkout or a new machine, run bootstrap first.
If you have not yet installed the required tools, see
[doc/guides/environment.md](doc/guides/environment.md) for platform-specific
instructions.

**Linux/macOS**

```sh
./scripts/bootstrap.sh
```

**Windows PowerShell**

```powershell
./scripts/bootstrap.ps1
```

**Linux/macOS**

```sh
./scripts/check.sh
```

**Windows PowerShell**

```powershell
./scripts/check.ps1
```

Or run CMake directly:

```sh
cmake --preset ninja-debug
cmake --build --preset ninja-debug
ctest --preset ninja-debug --output-on-failure
```

## Branches

Use short branch names:

- `feature/<topic>`
- `fix/<topic>`
- `refactor/<topic>`
- `infra/<topic>`
- `release/<version>`

Start new work from an up-to-date default branch:

```sh
git switch main
git pull
git switch -c infra/example-change
```

Use `master` instead of `main` when working in a clone whose default branch is
`master`.

## Commits And PRs

Use Conventional Commit style where practical:

```text
fix(parser): reject invalid delimiters
feat(cli): add version command
refactor(build): share test target helper
```

Before opening a PR:

- Run the smallest local checks that cover the change.
- Fill in the PR template sections that apply to the change.
- Explain behavioral, compatibility, or release impact.
- Add tests for behavior changes.
- Link to updated docs when the change affects build, test, install, release,
  security, or public API behavior.
- Keep unrelated cleanup out of feature or fix PRs.

Check, commit, and push the branch before opening a pull request:

```sh
git status
git diff --check
git add <changed-files>
git commit -m "infra: describe the change"
git push -u origin infra/example-change
```

Create the PR against `main` or `master` through GitHub, or with GitHub CLI:

```sh
gh pr create --base main --head infra/example-change --fill
```

Push follow-up commits to the same branch to update the existing PR:

```sh
git add <changed-files>
git commit -m "fix: address review feedback"
git push
```

After the PR is merged, update the default branch and delete the local topic
branch:

```sh
git switch main
git pull
git branch -d infra/example-change
git remote prune origin
```

Use the issue templates for bug reports, feature proposals, and infrastructure
maintenance requests.

## Architecture

- Keep public headers small and stable.
- Keep implementation details out of `include/`.
- Prefer explicit ownership and cleanup paths.
- Avoid adding abstractions until repeated use justifies them.
