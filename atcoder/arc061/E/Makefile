PROBLEM_NAME := $(notdir $(CURDIR))
TARGET       := $(PROBLEM_NAME)
SRC          := $(PROBLEM_NAME).cpp

CXX ?= clang++

BASEFLAGS := -std=c++20 \
  -O2 \
  -fdiagnostics-color=always \
  -Wall -Wextra -Wpedantic \
  -Wshadow -Wformat=2 -Wfloat-equal -Wconversion \
  -Wshift-sign-overflow \
  -Wcast-qual -Wcast-align \
  -Wno-unused-result -Wno-sign-conversion

DEBUGFLAGS := -g \
  -fsanitize=address,undefined \
  -fno-sanitize-recover=all

ifeq ($(DEBUG),true)
  CXXFLAGS := $(BASEFLAGS:-O2=) $(DEBUGFLAGS)
  LDFLAGS  := $(DEBUGFLAGS)
else
  CXXFLAGS := $(BASEFLAGS)
  LDFLAGS  :=
endif

all: $(TARGET)
.PHONY: all

%: %.cpp
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@

clean:
	-rm -rf $(TARGET)
.PHONY: clean

veryclean:
	-rm -rf $(TARGET) *.res
.PHONY: veryclean

rebuild: clean all
.PHONY: rebuild

TIMEBIN := /usr/bin/time
TIMEOPT := -p

run: $(TARGET)
	$(TIMEBIN) $(TIMEOPT) ./$(TARGET)
ifeq ($(DEBUG),true)
	@echo "Built with DEBUG (asan/ubsan) — may run slower."
endif
.PHONY: run

# Input -> Result
%.res: $(TARGET) %.in
	$(TIMEBIN) $(TIMEOPT) ./$(TARGET) < $*.in > $*.res
ifeq ($(DEBUG),true)
	@echo "Built with DEBUG (asan/ubsan) — may run slower."
endif
.PRECIOUS: %.res

GREEN := \033[0;32m
RED   := \033[0;31m
NC    := \033[0m   # No Color

__test_%: %.res %.out
	@echo "Testing $*..."
	@set -e; \
	if [ ! -f "$*.out" ]; then \
	  echo "$(RED)MISSING$(NC) - expected file '$*.out' not found"; exit 2; \
	fi; \
	if diff -q "$*.out" "$*.res" >/dev/null; then \
	  echo "$(GREEN)ACCEPT$(NC) - $*"; \
	else \
	  echo "$(RED)WRONG$(NC) - $*"; \
	  echo "---- diff (expected vs actual) ----"; \
	  diff -u "$*.out" "$*.res" | sed -E '\
	    s/^(\-.*)/\x1b[32m\1\x1b[0m/; \
	    s/^(\+.*)/\x1b[31m\1\x1b[0m/; \
	    s/^(@@.*)/\x1b[1m\1\x1b[0m/; \
	    s/^(--- .*)/\x1b[2m\1\x1b[0m/; \
	    s/^(\+\+\+ .*)/\x1b[2m\1\x1b[0m/'; \
	  echo "-----------------------------------"; \
	  exit 1; \
	fi
.PHONY: __test_%

CASES := $(sort $(basename $(wildcard *.in)))
TESTS := $(sort $(basename $(wildcard *.out)))

runs: $(patsubst %,%.res,$(CASES))
.PHONY: runs

solve: runs
.PHONY: solve

test: $(patsubst %,__test_%,$(TESTS))
.PHONY: test
