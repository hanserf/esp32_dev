set(COMPONENT_SRCS "*.c")
set(COMPONENT_ADD_INCLUDEDIRS ../include/cmd/)
set(COMPONENT_REQUIRES console spi_flash)

register_component()
