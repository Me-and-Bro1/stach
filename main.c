#include "helper.h"
#include <stdbool.h>
#include <string.h>

typedef struct {
  const char *input_file;
  const char *output_file;
  uint64_t columns;     // -c [cols] Specifies the number of octets (bytes) to
                        // display per line (default is 16).
  uint64_t group_bytes; // -g [bytes] Sets how many bytes are grouped together
                        // (default is 2).
  uint64_t length; // -l [len] Limits the output to a specific number of bytes.
  uint64_t seek; // -s [offset] Starts the dump at a specific byte offset in the
                 // file.
  bool autoskip; // -a Replaces duplicate or null lines with an asterisk (*) to
                 // shorten output.
  bool binary_bump; // -b Displays the output in binary bits (0s and 1s) instead
                    // of hex.
  bool plain;     // -p Outputs a continuous hex string without line numbers or
                  // ASCII characters.
  bool uppercase; // -u Uses uppercase hexadecimal digits instead of lowercase.
} ProgramArgs;

ProgramArgs init_args(const int argc, const char **argv) {
  ProgramArgs args = {
      .input_file = NULL,
      .output_file = NULL,
      .autoskip = false,
      .binary_bump = false,
      .plain = false,
      .uppercase = false,
      .columns = 16,
      .group_bytes = 2,
      .length = -1ull,
      .seek = 0,
  };

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];

    if (strcmp(arg, "--") == 0) {
      if (i + 1 < argc)
        args.input_file = argv[++i];
      if (i + 1 < argc)
        args.output_file = argv[++i];
      break;
    }

    if (arg[0] != '-') {
      if (!args.input_file)
        args.input_file = arg;
      else if (!args.output_file)
        args.output_file = arg;
      else {
        fprintf(stderr, "Error: unexpected argument '%s'\n", arg);
        exit(EXIT_FAILURE);
      }
      continue;
    }

    if (arg[1] == '\0') {
      fprintf(stderr, "Error: invalid option '%s'\n", arg);
      exit(EXIT_FAILURE);
    }

    const char opt = arg[1];
    if (arg[2] != '\0') {
      fprintf(stderr, "Error: unsupported option format '%s'\n", arg);
      exit(EXIT_FAILURE);
    }

    switch (opt) {
    case 'a':
      args.autoskip = true;
      break;
    case 'b':
      args.binary_bump = true;
      break;
    case 'p':
      args.plain = true;
      break;
    case 'u':
      args.uppercase = true;
      break;
    case 'c':
      if (++i >= argc) {
        fprintf(stderr, "Error: -c requires a value\n");
        exit(EXIT_FAILURE);
      }
      args.columns = parse_uint(argv[i], "-c");
      if (args.columns == 0) {
        fprintf(stderr, "Error: -c must be greater than 0\n");
        exit(EXIT_FAILURE);
      }
      break;
    case 'g':
      if (++i >= argc) {
        fprintf(stderr, "Error: -g requires a value\n");
        exit(EXIT_FAILURE);
      }
      args.group_bytes = parse_uint(argv[i], "-g");
      if (args.group_bytes == 0) {
        fprintf(stderr, "Error: -g must be greater than 0\n");
        exit(EXIT_FAILURE);
      }
      break;
    case 'l':
      if (++i >= argc) {
        fprintf(stderr, "Error: -l requires a value\n");
        exit(EXIT_FAILURE);
      }
      args.length = parse_uint(argv[i], "-l");
      if (args.length == 0) {
        fprintf(stderr, "Error: -l must be greater than 0\n");
        exit(EXIT_FAILURE);
      }
      break;
    case 's':
      if (++i >= argc) {
        fprintf(stderr, "Error: -s requires a value\n");
        exit(EXIT_FAILURE);
      }
      args.seek = parse_uint(argv[i], "-s");
      break;
    default:
      fprintf(stderr, "Error: unknown option '-%c'\n", opt);
      exit(EXIT_FAILURE);
    }
  }

  return args;
}

void print_args(const ProgramArgs *args) {
  printf("Input file: %s\n", args->input_file);
  printf("Output file: %s\n", args->output_file);
  printf("Autoskip: %s\n", args->autoskip ? "true" : "false");
  printf("Binary bump: %s\n", args->binary_bump ? "true" : "false");
  printf("Plain: %s\n", args->plain ? "true" : "false");
  printf("Uppercase: %s\n", args->uppercase ? "true" : "false");
  printf("Columns: %lu\n", args->columns);
  printf("Group bytes: %lu\n", args->group_bytes);
  printf("Length: %lu\n", args->length);
  printf("Seek: %lu\n", args->seek);
  printf("\n");
}

int main(const int argc, const char **argv) {
  const ProgramArgs args = init_args(argc, argv);
  print_args(&args);
  return 0;
}
