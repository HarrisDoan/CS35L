#!/usr/bin/env python3.10
import random
import argparse

def main():
    parser = argparse.ArgumentParser()
    mutually_exclusive_group = parser.add_mutually_exclusive_group()
    mutually_exclusive_group.add_argument("-e", "--echo", action="store_true",
                                            help="Treats each command LO through HI as the input line.") 
    mutually_exclusive_group.add_argument("-i", "--input-range", metavar="LO-HI",
                                            help="Acts as if the input came from a file containing the range, only one per line.")
    
    parser.add_argument("-n", "--head-count", metavar="COUNT", type=int,
                        help="Output at most countt lines.")
    parser.add_argument("-r", "--repeat", action="store_true",
                        help="Repeat output lines are acceptable.")
    args, unknownargs = parser.parse_known_args()

    if args.echo:
        lines = unknownargs

    elif args.input_range:
        if len(unknownargs) > 0:
            parser.error("extra operand: {}".format(unknownargs[0]))
        if "-" not in args.input_range:
            parser.error("invalid input range: {}".format(args.input_range))
        try:
            lo, hi = args.input_range.split("-")
            if  not lo.isdigit() or not hi.isdigit():
                raise ValueError
            lo = int(lo)
            hi = int(hi)
            if lo > hi:
                raise ValueError
        except ValueError:
            parser.error("invalid input range: {}".format(args.input_range))
        lines = [str(x) for x in range(lo, hi)]
    else:
        if (len (unknownargs) == 0) or unknownargs[0] == "-":
            file = "/dev/stdin"
        elif (len(unknownargs) >= 2):
            parser.error(f"extra operand {unknownargs[1]}")
        else:
            file = unknownargs[0]
        try:
            open(file)
        except FileNotFoundError:
            parser.error(f"{file}: No such file or directory")
        lines = open(file).readlines()
    
    head_count = 0
    if args.head_count:
        try:
            head_count = int(args.head_count)
        except ValueError:
            parser.error("invalid line count: '{}'".format(args.head_count))
    
    if args.repeat:
        while head_count >= 1 or not args.head_count:
            chosen_line = random.choice(lines).rstrip()
            print(chosen_line)
            head_count -= 1
    else:
        if not args.head_count or head_count > len(lines):
            head_count = len(lines)
        lines = random.sample(lines, k=head_count)
        for line in lines:
            print(line.rstrip())

if __name__ == "__main__":
    main()
