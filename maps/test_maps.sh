#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Test results arrays
declare -a GOOD_RESULTS
declare -a BAD_RESULTS
declare -a MAIN_RESULTS

echo -e "${CYAN}========================================${NC}"
echo -e "${CYAN}         cub3D Map Tester              ${NC}"
echo -e "${CYAN}========================================${NC}"
echo

# Check if cub3D executable exists
if [ ! -f "./cub3D" ]; then
    echo -e "${RED}Error: cub3D executable not found!${NC}"
    echo -e "${YELLOW}Running make to build the project...${NC}"
    make
    if [ $? -ne 0 ]; then
        echo -e "${RED}Build failed! Exiting.${NC}"
        exit 1
    fi
fi

echo -e "${BLUE}Testing executable: $(pwd)/cub3D${NC}"
echo

# Function to test a single map file
test_map() {
    local map_file="$1"
    local expected_result="$2"  # "good" or "bad"
    local category="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    printf "%-50s" "Testing: $(basename "$map_file")"
    
    # Run the program and capture output and exit code
    output=$(./cub3D "$map_file" 2>&1)
    exit_code=$?
    
    # Determine if test passed based on expected result
    if [ "$expected_result" = "good" ]; then
        # For good maps, we expect exit code 0 (success)
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}[PASS]${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            if [ "$category" = "good" ]; then
                GOOD_RESULTS+=("✅ $(basename "$map_file")")
            elif [ "$category" = "main" ]; then
                MAIN_RESULTS+=("✅ $(basename "$map_file")")
            fi
        else
            echo -e "${RED}[FAIL]${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            if [ "$category" = "good" ]; then
                GOOD_RESULTS+=("❌ $(basename "$map_file") (Exit: $exit_code)")
            elif [ "$category" = "main" ]; then
                MAIN_RESULTS+=("❌ $(basename "$map_file") (Exit: $exit_code)")
            fi
            echo -e "${RED}   Error output: $output${NC}"
        fi
    else
        # For bad maps, we expect non-zero exit code (failure)
        if [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}[PASS]${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            BAD_RESULTS+=("✅ $(basename "$map_file")")
        else
            echo -e "${RED}[FAIL]${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            BAD_RESULTS+=("❌ $(basename "$map_file") (Should have failed but passed)")
            echo -e "${RED}   Unexpected success for bad map!${NC}"
        fi
    fi
}

# Test main maps directory
echo -e "${PURPLE}=== Testing Main Maps ====${NC}"
for map_file in maps/*.cub; do
    if [ -f "$map_file" ]; then
        test_map "$map_file" "good" "main"
    fi
done
echo

# Test good maps
echo -e "${GREEN}=== Testing Good Maps ====${NC}"
for map_file in maps/good/*.cub; do
    if [ -f "$map_file" ]; then
        test_map "$map_file" "good" "good"
    fi
done
echo

# Test bad maps
echo -e "${RED}=== Testing Bad Maps ====${NC}"
for map_file in maps/bad/*; do
    if [ -f "$map_file" ]; then
        test_map "$map_file" "bad" "bad"
    fi
done
echo

# Summary
echo -e "${CYAN}========================================${NC}"
echo -e "${CYAN}              SUMMARY                   ${NC}"
echo -e "${CYAN}========================================${NC}"
echo -e "${BLUE}Total Tests: $TOTAL_TESTS${NC}"
echo -e "${GREEN}Passed: $PASSED_TESTS${NC}"
echo -e "${RED}Failed: $FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed! 🎉${NC}"
else
    echo -e "\n${RED}❌ Some tests failed!${NC}"
fi

echo -e "\n${YELLOW}=== Detailed Results ===${NC}"

# Show main maps results
if [ ${#MAIN_RESULTS[@]} -gt 0 ]; then
    echo -e "\n${PURPLE}Main Maps:${NC}"
    for result in "${MAIN_RESULTS[@]}"; do
        echo "  $result"
    done
fi

# Show good maps results
if [ ${#GOOD_RESULTS[@]} -gt 0 ]; then
    echo -e "\n${GREEN}Good Maps:${NC}"
    for result in "${GOOD_RESULTS[@]}"; do
        echo "  $result"
    done
fi

# Show bad maps results
if [ ${#BAD_RESULTS[@]} -gt 0 ]; then
    echo -e "\n${RED}Bad Maps:${NC}"
    for result in "${BAD_RESULTS[@]}"; do
        echo "  $result"
    done
fi

echo -e "\n${CYAN}========================================${NC}"

# Exit with appropriate code
if [ $FAILED_TESTS -eq 0 ]; then
    exit 0
else
    exit 1
fi
