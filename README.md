# GREP

The `grep` command line utility was first introduced in 1974 as a method of searching files and directories using regular expressions. This is just me recreating it as a guide from beginner to advanced usage.

### How to Use

```bash
# Basic usage:
grep "pattern" filename

#At a Beginner Level:
grep "apple" fruits.txt

#At an Intermediate Level:
grep -i "apple" fruits.txt    # Case-insensitive search
grep -n "apple" fruits.txt    # Show line numbers
grep -r "apple" ./directory   # Search recursively in a folder
grep -c "apple" fruits.txt    # Count matches

#At an Advanced Level:
grep "^apple" fruits.txt      # Lines starting with "apple"
grep "apple$" fruits.txt      # Lines ending with "apple"
grep "a.p" fruits.txt         # Lines containing a pattern with any single character
grep -v "apple" fruits.txt    # Show lines that do NOT contain "apple"
dmesg | grep "usb"            # Search the output of another command


