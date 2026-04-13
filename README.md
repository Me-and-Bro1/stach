# Stach

![Build Status](https://github.com/Me-and-Bro1/stach/actions/workflows/makefile.yml/badge.svg)

Stach is hexdumper software written in C.

## Building

Prerequisites: `clang` or `gcc` compiler and `make` utility.

To build Stach, run the following command in the terminal:

```bash
# Using clang
make

# Using gcc
make CC=gcc
```

## Usage

To use Stach, run the following command in the terminal:

```bash
./stach [options] <input_file> [output_file]
```

### Options

- `-s <offset>`: Start offset (default: 0)
- `-l <length>`: Length to dump (default: until end of file)
- `-c <columns>`: Number of columns (default: 16)
- `-g <group_size>`: Group size for hexadecimal output (default: 2)
- `-a`: Replaces duplicate or null lines with an asterisk (*) to shorten output. **Not implemented yet**
- `-b`: Display binary output instead of hexadecimal
- `-p`: Outputs a continuous hex string without line numbers or ASCII characters. **Not implemented yet**
- `-u`: Use uppercase letters for hexadecimal output (default: lowercase)
