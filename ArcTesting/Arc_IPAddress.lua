
Arc_IPAddress = {

	hostnameLookup = function( hostname )
	
		addr = Arc_IPAddress()
		rawset(rawget(getmetatable(addr), "private"), "arc_ipaddress", arc_hostnameLookup(hostname))

		return addr

		end
}

Arc_IPAddress_methods = {

	getA = function( self )
	
		return arc_ipaddress_getA(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"))

		end,
	getB = function( self )
	
		return arc_ipaddress_getB(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"))

		end,
	getC = function( self )
	
		return arc_ipaddress_getC(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"))

		end,
	getD = function( self )
	
		return arc_ipaddress_getD(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"))

		end,
	setA = function( self, a )
	
		return arc_ipaddress_setA(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"), a)

		end,
	setB = function( self, b )
	
		return arc_ipaddress_setB(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"), b)

		end,
	setC = function( self, c )
	
		return arc_ipaddress_setC(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"), c)

		end,
	setD = function( self, d )
	
		return arc_ipaddress_setD(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"), d)

		end

}

function Arc_IPAddress:new_field( key, value )
	arc_error("Arc_IPAddress does not support new fields")
end

function Arc_IPAddress:dtor()
	arc_ipaddress_destroy(rawget(rawget(getmetatable(self), "private"), "arc_ipaddress"))
end

function Arc_IPAddress:ctor( a, b, c, d )
	local i = {}
	local i_mt = {
					__index = Arc_IPAddress_methods,
					__newindex = Arc_IPAddress.new_field,
					__gc = Arc_IPAddress.dtor,
					private = { }
				 }
	setmetatable(i, i_mt)

	rawset(rawget(getmetatable(i), "private"), "arc_ipaddress", arc_ipaddress_create(a, b, c, d))

	return i
end

setmetatable(Arc_IPAddress, {__call = Arc_IPAddress.ctor})