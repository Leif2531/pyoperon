vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO heal-research/operon
    REF f0ac2228fdce14b4a5000377b9462a5b29aa6290
    SHA512 7c0a6008995304691e122256cd22c0c7edb985d6512b306aa8be6bb36977b502580ef618a0e4a4988f6d7048cf686e14e8f567056bc650be1ae6b86c2fb5ad55
    HEAD_REF main
    PATCHES
        cpp17.patch
)

include("${VCPKG_ROOT_DIR}/ports/vcpkg-cmake/vcpkg_cmake_build.cmake")
include("${VCPKG_ROOT_DIR}/ports/vcpkg-cmake/vcpkg_cmake_install.cmake")
include("${VCPKG_ROOT_DIR}/ports/vcpkg-cmake-config/vcpkg_cmake_config_fixup.cmake")

set(VCPKG_BUILD_TYPE release)

string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "dynamic" OPERON_SHARED_LIBS)

vcpkg_configure_cmake(
  SOURCE_PATH "${SOURCE_PATH}"
  PREFER_NINJA
  OPTIONS
        -DBUILD_TESTING=OFF
        -DBUILD_EXAMPLES=OFF
        -DBUILD_SHARED_LIBS=${OPERON_SHARED_LIBS}
        -DBUILD_CLI_PROGRAMS=OFF
        -DUSE_OPENLIBM=OFF
        -DUSE_SINGLE_PRECISION=ON
  MAYBE_UNUSED_VARIABLES
        BUILD_TESTING
        USE_OPENLIBM
)
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME operon DO_NOT_DELETE_PARENT_CONFIG_PATH)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include"
                    "${CURRENT_PACKAGES_DIR}/debug/share")

file(
  INSTALL "${SOURCE_PATH}/LICENSE"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright)
