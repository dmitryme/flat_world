import flatbuffers as fb
from python.proto import Order

# encode
b = fb.Builder(0)

Order.OrderStart(b)
Order.OrderAddId(b, 100)
o = Order.OrderEnd(b)

b.Finish(o)
out = bytes(b.Output())

# s = ""
# for i in out:
    # s += "0x{:02x}, ".format(i)
# print(s)

# decode self
order = Order.Order.GetRootAsOrder(out, 0)
print(order.Id())

# decode C-encoded Order
c_enc = b'\x08\x00\x00\x00\x76\x30\x30\x31\xf8\xff\xff\xff\x64\x00\x00\x00\x06\x00\x08\x00\x04\x00'

order = Order.Order.GetRootAsOrder(out, 0)
print(order.Id())
