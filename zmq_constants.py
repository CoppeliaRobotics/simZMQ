import argparse
import os.path
import re

parser = argparse.ArgumentParser(description='Generate ZMQ constants from zmq.h file.')
parser.add_argument('out_file', type=str, default=None, help='the output .cpp file')
parser.add_argument('zmq_dirs', type=str, nargs='+', default=None, help='the location of zmq.h')
args = parser.parse_args()

if args is False:
    SystemExit

zmq_h = None
for d in args.zmq_dirs:
    x = os.path.join(d, 'zmq.h')
    if os.path.isfile(x):
        zmq_h = x
        break

if not zmq_h:
    raise Exception('zmq.h not found in any of the specified locations')

def skip(sym):
    if sym == 'EXPORT': return True
    if re.match(r'DEFINED_\w+', sym): return True
    if re.match(r'VERSION(|_MAJOR|_MINOR|_PATCH)', sym): return True

with open(args.out_file, 'w') as f_out:
    f_out.write('#undef __ZMQ_H_INCLUDED__\n')
    with open(zmq_h, 'r') as f_in:
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
