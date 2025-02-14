workspace("HotelManagementService")
configurations({ "Debug", "Release" })
targetname("HotelManagementService.out")

project("HotelManagementService")
kind("ConsoleApp")
language("C")
targetdir("bin")
files({
	"./src/*.h",
	"./src/*.c",
})

filter("configurations:Debug")
defines({ "DEBUG" })
symbols("On")
