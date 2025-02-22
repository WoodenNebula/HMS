workspace("HotelManagementService")
configurations({ "Debug", "Release" })
targetname("HotelManagementService.out")

project("HotelManagementService")
kind("ConsoleApp")
language("C")
targetdir("bin")
files({
	"./src/**.h",
	"./src/**.c",
})

filter "system:windows"
    defines { "WINDOWS" }
filter {}

filter "system:linux"
    defines { "LINUX" }
filter {}


filter("configurations:Debug")
defines({ "DEBUG" })
symbols("On")
