# CMakeList.txt : CMake project for BUDe, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

project ("BUDe"	VERSION 0.5 DESCRIPTION "A friendly discord bot!")

add_subdirectory(libs/DPP)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} 
		src/BUDe.cpp
		src/BUDe.h
		src/Commands/Core/Command.h
		src/Commands/PingCommand.h
		src/Commands/RPSCommand.h
		src/Commands/AnnouncementCommand.h
		src/Commands/CreditsCommand.h
		src/Commands/AvatarCommand.h
		src/Commands/AttachmentCommand.h
		src/Commands/EmbedCommand.h
		src/Listeners/rps_listener.h
        src/Utils/ComponentBuilder.h
		src/Utils/EmbedBuilder.h
		src/Utils/ComponentData.h
		src/Listeners/command_listener.cpp
        src/Listeners/command_listener.h
		src/Listeners/rps_listener.cpp
		src/Commands/EchoCommand.cpp
		src/Commands/EchoCommand.h
		src/Commands/EmbedCommand.cpp
		src/Commands/PMCommand.cpp
		src/Commands/PMCommand.h
        src/Commands/CreateThreadCommand.cpp
        src/Commands/CreateThreadCommand.h
		src/Commands/MessageThreadCommand.cpp
		src/Commands/MessageThreadCommand.h
        src/Commands/AvatarCommand.cpp
)

target_link_libraries(${PROJECT_NAME}
		dpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
		libs/DPP/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
		CMAKE_STANDARD 17
		CMAKE_STANDARD_REQUIRED ON
)

# TODO: Add tests and install targets if needed.
