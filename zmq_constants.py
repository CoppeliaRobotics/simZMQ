import argparse
import re

parser = argparse.ArgumentParser(description='Generate ZMQ constants from zmq.h file.')
parser.add_argument('out_file', type=str, default=None, help='the output .cpp file')
parser.add_argument('zmq_header', type=str, default=None, help='the path to the zmq.h file')
args = parser.parse_args()

if args is False:
    SystemExit

def skip(sym):
    if sym == 'EXPORT': return True
    if re.match(r'DEFINED_\w+', sym): return True
    if re.match(r'VERSION(|_MAJOR|_MINOR|_PATCH)', sym): return True

with open(args.out_file, 'w') as f_out:
    f_out.write('#undef __ZMQ_H_INCLUDED__\n')
    with open(args.zmq_header, 'r') as f_in:
        for line in f_in:
            if m := re.match('#define\s+ZMQ_(\w+)\s+([^\s]+)', line):
                sym = m.group(1)
                if not skip(sym):
                    f_out.write(f'sim::registerScriptVariable("simZMQ.{sym}", ZMQ_{sym}, 0);')
                    f_out.write('\n')
            elif m := re.match('#if.*', line):
                f_out.write(line + '\n')
            elif m := re.match('#endif.*', line):
                f_out.write(line + '\n')
