vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO martinus/unordered_dense
    REF fd80dad6285286db5be6d2588cc7ddb624db7e5a
    SHA512 7c7039012b6cef0ea7722cc384be839fea043093cd20f2b1e6328630d1cc1a2d57756e2a313ea7b876cb94b2ef761be7c2b272e0a7b0326263eaa723d8160383
    HEAD_REF main
)

include("${VCPKG_ROOT_DIR}/ports/vcpkg-cmake/vcpkg_cmake_build.cmake")
include("${VCPKG_ROOT_DIR}/ports/vcpkg-cmake/vcpkg_cmake_install.cmake")
include("${VCPKG_ROOT_DIR}/ports/vcpkg-cmake-config/vcpkg_cmake_config_fixup.cmake")

set(VCPKG_BUILD_TYPE release)

vcpkg_configure_cmake(
  SOURCE_PATH "${SOURCE_PATH}"
  PREFER_NINJA
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME unordered_dense CONFIG_PATH lib/cmake/unordered_dense DO_NOT_DELETE_PARENT_CONFIG_PATH)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include"
                    "${CURRENT_PACKAGES_DIR}/debug/share"
                    "${CURRENT_PACKAGES_DIR}/lib")

vcpkg_fixup_pkgconfig()

file(
  INSTALL "${SOURCE_PATH}/LICENSE"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright)

