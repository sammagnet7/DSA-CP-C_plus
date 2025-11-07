#!/usr/bin/env bash
exe="$1"
shift || true

# Green start marker
printf '\x1b[1;32m=== Running Program ===\x1b[0m\n'

# Run program directly (preserves normal stdout/stderr & interactivity)
#"$exe" "$@"

# If you want every output line yellow, replace the above with:
"$exe" "$@" | sed $'s/.*/\x1b[33m&\x1b[0m/'

# Blue finish marker
ret=$?
printf '\x1b[1;34m=== Program Finished (exit=%d) ===\x1b[0m\n' "$ret"
exit "$ret"
