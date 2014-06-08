
Arc_Socket = {}

Arc_Socket_methods = {

	connect = function( self, dest, port)

		if (type(dest) ~= "string") then
			dest = rawget(rawget(getmetatable(dest), "private"), "arc_ipaddress")
		end

		arc_socket_connect(rawget(rawget(getmetatable(self), "private"), "arc_socket"), 
			dest, port)

		end,
	disconnect = function( self )
	
		arc_socket_connect(rawget(rawget(getmetatable(self), "private"), "arc_socket"))

		end,
	sendString = function( self, str, nullTerm )
	
		arc_socket_sendString(rawget(rawget(getmetatable(self), "private"), "arc_socket"),
			str, nullTerm)

		end,
	sendLine = function( self, str, nullTerm )
	
		arc_socket_sendString(rawget(rawget(getmetatable(self), "private"), "arc_socket"),
			str .. "\n", nullTerm)

		end,
	recvLine = function( self )
	
		return arc_socket_recvLine(rawget(rawget(getmetatable(self), "private"), "arc_socket"))

		end,
	isOpen = function( self )
	
		return arc_socket_isOpen(rawget(rawget(getmetatable(self), "private"), "arc_socket"))

		end


}

function Arc_Socket:new_field( key, value )
	arc_error("Arc_Socket does not support new fields")
end

function Arc_Socket:dtor()
	arc_socket_destroy(rawget(rawget(getmetatable(self), "private"), "arc_socket"))
end

function Arc_Socket:ctor( dest, port )
	local s = {}
	local s_mt = {
					__index = Arc_Socket_methods,
					__newindex = Arc_Socket.new_field,
					__gc = Arc_Socket.dtor,
					private = { }
				 }
	setmetatable(s, s_mt)

	rawset(rawget(getmetatable(s), "private"), "arc_socket", arc_socket_create())

	if (dest ~= nil and port ~= nil) then
		s:connect(dest, port)
	end

	return s
end

setmetatable(Arc_Socket, {__call = Arc_Socket.ctor})