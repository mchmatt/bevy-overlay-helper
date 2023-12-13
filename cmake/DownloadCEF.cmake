function(DownloadCEF platform version download_dir)
    # Specify the binary distribution type and download directory.
  set(CEF_DISTRIBUTION "cef_binary_${version}_${platform}")
  set(CEF_DOWNLOAD_DIR "${download_dir}")

  # The location where we expect the extracted binary distribution.
  set(CEF_ROOT "${CMAKE_SOURCE_DIR}/libcef" CACHE INTERNAL "CEF_ROOT")

  # Download and/or extract the binary distribution if necessary.
  if(NOT IS_DIRECTORY "${CEF_ROOT}")
    set(CEF_DOWNLOAD_FILENAME "${CEF_DISTRIBUTION}.tar.bz2")
    set(CEF_DOWNLOAD_PATH "${CEF_DOWNLOAD_DIR}/${CEF_DOWNLOAD_FILENAME}")
    if(NOT EXISTS "${CEF_DOWNLOAD_PATH}")
      set(CEF_DOWNLOAD_URL "https://cef-builds.spotifycdn.com/${CEF_DOWNLOAD_FILENAME}")
      string(REPLACE "+" "%2B" CEF_DOWNLOAD_URL_ESCAPED ${CEF_DOWNLOAD_URL})

      # Download the SHA1 hash for the binary distribution.
      message(STATUS "Downloading ${CEF_DOWNLOAD_PATH}.sha1 from ${CEF_DOWNLOAD_URL_ESCAPED}...")
      file(DOWNLOAD "${CEF_DOWNLOAD_URL_ESCAPED}.sha1" "${CEF_DOWNLOAD_PATH}.sha1")
      file(READ "${CEF_DOWNLOAD_PATH}.sha1" CEF_SHA1)

      # Download the binary distribution and verify the hash.
      message(STATUS "Downloading ${CEF_DOWNLOAD_PATH}...")
      file(
        DOWNLOAD "${CEF_DOWNLOAD_URL_ESCAPED}" "${CEF_DOWNLOAD_PATH}"
        EXPECTED_HASH SHA1=${CEF_SHA1}
        SHOW_PROGRESS
        )
    endif()

    # Extract the binary distribution.
    message(STATUS "Extracting ${CEF_DOWNLOAD_PATH}...")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xzf "${CEF_DOWNLOAD_DIR}/${CEF_DOWNLOAD_FILENAME}"
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      )

    file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/libcef")
    file(RENAME "${CMAKE_SOURCE_DIR}/${CEF_DISTRIBUTION}" "${CMAKE_SOURCE_DIR}/libcef")

  endif()
endfunction()