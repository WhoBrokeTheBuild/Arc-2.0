
io.write("Hostname or IP: ")
hostname = io.read()

addr = Arc_IPAddress.hostnameLookup(hostname)

io.write("Port: ")
port = io.read()

io.write("Path: /")
path = io.read()

io.write("Connecting to ", addr:getA(), ".", addr:getB(), ".", addr:getC(), ".", addr:getD(), "\n")

sock = Arc_Socket()
sock:connect(addr, port)

sock:sendLine("GET /" .. path .. " HTTP/1.0", false)
sock:sendLine("User-Agent: Arc", false)
sock:sendLine("", false)

while sock:isOpen() do

print(sock:recvLine())

end

sock:disconnect()
sock = nil

collectgarbage()
