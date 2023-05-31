# ZeroMQ plugin for CoppeliaSim

### Compiling

1. Install required packages for simStubsGen: see simStubsGen's [README](https://github.com/CoppeliaRobotics/include/blob/master/simStubsGen/README.md)
2. Checkout, compile and install into CoppeliaSim:
```sh
$ git clone https://github.com/CoppeliaRobotics/simZMQ.git
$ cd simZMQ
$ git checkout coppeliasim-v4.5.0-rev0
$ mkdir -p build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ cmake --build .
$ cmake --install .
```

NOTE: replace `coppeliasim-v4.5.0-rev0` with the actual CoppeliaSim version you have.

### Documentation

Refer to the [ZeroMQ API Reference](http://api.zeromq.org) and the [ZeroMQ Guide](https://zguide.zeromq.org).

When using the ZMQ plugin, replace the `zmq_` prefix with `simZMQ.`.

E.g., the hello world example from the guide:

```lua
-- requester:

function sysCall_init()
    corout=coroutine.create(coroutineMain)
end

function sysCall_actuation()
    if coroutine.status(corout)~='dead' then
        local ok,errorMsg=coroutine.resume(corout)
        if errorMsg then
            error(debug.traceback(corout,errorMsg),2)
        end
    end
end

function coroutineMain()
    print('Connecting to hello world server...')
    context=simZMQ.ctx_new()
    requester=simZMQ.socket(context,simZMQ.REQ)
    simZMQ.connect(requester,'tcp://localhost:5555')

    for request_nbr=0,10 do
        print('-----------------------------------------')
        local data='Hello'
        print('[requester] Sending "%s"...',data)
        simZMQ.send(requester,data,0)
        local rc,data=simZMQ.recv(requester,0)
        print('[requester] Received "%s"',data)
    end
end

function sysCall_cleanup()
    simZMQ.close(requester)
    simZMQ.ctx_term(context)
end
```

```lua
-- responder:

function sysCall_init()
    corout=coroutine.create(coroutineMain)
end

function sysCall_actuation()
    if coroutine.status(corout)~='dead' then
        local ok,errorMsg=coroutine.resume(corout)
        if errorMsg then
            error(debug.traceback(corout,errorMsg),2)
        end
    end
end

function coroutineMain()
    context=simZMQ.ctx_new()
    responder=simZMQ.socket(context,simZMQ.REP)
    local rc=simZMQ.bind(responder,'tcp://*:5555')
    if rc~=0 then error('failed bind') end

    while true do
        local rc,data=simZMQ.recv(responder,0)
        print('[responder] Received "%s"',data)
        data='World'
        print('[responder] Sending "%s"...',data)
        simZMQ.send(responder,data,0)
    end
end

function sysCall_cleanup()
    simZMQ.close(responder)
    simZMQ.ctx_term(context)
end
```

Note: functions that block (send, recv, and similar) are wrapped by a busy-waiting loop, that allows CoppeliaSim to pre-empt or suspend the script while it is waiting for the socket to be ready.

Note: the only funciton not part of the ZeroMQ API is `simZMQ.ctx_singleton()`, useful for using a global context across many scripts (required for _inproc_ to work).
