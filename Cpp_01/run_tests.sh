#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT_DIR"

failures=0
echo "Building all exercises..."
for d in ex*; do
  if [ -f "$d/Makefile" ]; then
    echo " make -C $d"
    make -C "$d" >/dev/null || true
  fi
done

check() {
  local name="$1"; shift
  echo -n "Test: $name ... "
  if "$@" >/tmp/run_tests_out 2>&1; then
    echo "OK"
  else
    echo "FAIL"
    failures=$((failures+1))
  fi
}

check_exe_output_contains() {
  local exe="$1"; shift
  local mustContain="$1"; shift
  "$exe" "$@" >/tmp/run_tests_out 2>&1 || true
  if grep -q -F "$mustContain" /tmp/run_tests_out; then
    echo "OK"
    return 0
  else
    echo "FAIL (no '$mustContain')"
    failures=$((failures+1))
    return 1
  fi
}

echo
echo "Running tests..."

find_exe() {
  local d="$1"
  find "$d" -maxdepth 1 -type f -executable ! -name '*.o' | sed -n '1p' || true
}

run_and_check() {
  local exdir="$1"; shift
  local check_type="$1"; shift || true
  local exe
  exe=$(find_exe "$exdir" || true)
  if [ -z "$exe" ]; then
    echo "$exdir: NO EXECUTABLE FOUND"
    failures=$((failures+1))
    return
  fi
  echo -n "$exdir: "
  case "$check_type" in
    brain)
      "$exe" >/tmp/run_tests_out 2>&1 || true
      if grep -q "Brai" /tmp/run_tests_out && grep -q "is destroyed" /tmp/run_tests_out; then echo "PASS"; else echo "FAIL"; failures=$((failures+1)); fi
      ;;
    horde)
      "$exe" >/tmp/run_tests_out 2>&1 || true
      if grep -q "HordeZombie" /tmp/run_tests_out && grep -q "is destroyed" /tmp/run_tests_out; then echo "PASS"; else echo "FAIL"; failures=$((failures+1)); fi
      ;;
    brainstr)
      "$exe" >/tmp/run_tests_out 2>&1 || true
      if grep -q "HI THIS IS BRAIN" /tmp/run_tests_out; then echo "PASS"; else echo "FAIL"; failures=$((failures+1)); fi
      ;;
    attacks)
      "$exe" >/tmp/run_tests_out 2>&1 || true
      if grep -q "Bob attacks" /tmp/run_tests_out && grep -q "Jim attacks" /tmp/run_tests_out; then echo "PASS"; else echo "FAIL"; failures=$((failures+1)); fi
      ;;
    replace)
      "$exe" ex04/sample.txt s1 s2 >/tmp/run_tests_out 2>&1 || true
      if [ -f ex04/sample.txt.replace ] && grep -q "s2" ex04/sample.txt.replace; then echo "PASS"; else echo "FAIL"; failures=$((failures+1)); fi
      ;;
    harl)
      "$exe" >/tmp/run_tests_out 2>&1 || true
      if grep -q "\[ DEBUG \]" /tmp/run_tests_out && grep -q "\[ ERROR \]" /tmp/run_tests_out; then echo "PASS"; else echo "FAIL"; failures=$((failures+1)); fi
      ;;
    harlfilter)
      "$exe" WARNING >/tmp/run_tests_out 2>&1 || true
      if grep -q "\[ WARNING \]" /tmp/run_tests_out && grep -q "\[ ERROR \]" /tmp/run_tests_out; then echo "PASS"; else echo "FAIL"; failures=$((failures+1)); fi
      ;;
    *)
      echo "UNKNOWN CHECK: $check_type"; failures=$((failures+1));;
  esac
}

# Run checks using detected executables
run_and_check ex00 brain
run_and_check ex01 horde
run_and_check ex02 brainstr
run_and_check ex03 attacks
run_and_check ex04 replace
run_and_check ex05 harl
run_and_check ex06 harlfilter

echo
if [ "$failures" -eq 0 ]; then
  echo "ALL TESTS PASSED"
else
  echo "$failures test(s) failed"
  exit 2
fi
