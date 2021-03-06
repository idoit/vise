add_library( flat_desc_file flat_desc_file.cpp )
target_link_libraries( flat_desc_file )


add_library( train_assign train_assign.cpp )
target_link_libraries( train_assign
    ViseMessageQueue
    feat_getter
    flat_desc_file
    image_util
    par_queue
    same_random
    clst_centres # added by @Abhishek to support compilation in Mac
    ${fastann_LIBRARIES} # added by @Abhishek to support compilation in Mac
    ${Boost_LIBRARIES} )

add_library( train_descs train_descs.cpp )
target_link_libraries( train_descs
    ViseMessageQueue
    clst_centres
    par_queue
    same_random # added by @Abhishek to support compilation in Mac
    image_util # added by @Abhishek to support compilation in Mac
    ${fastann_LIBRARIES}
    ${Boost_LIBRARIES} )

add_library( train_hamming train_hamming.cpp )
target_link_libraries( train_hamming
    ViseMessageQueue
    clst_centres
    flat_desc_file
    median_computer
    par_queue
    protobuf_util
    same_random
    hamming_data.pb # added by @Abhishek to support compilation in Mac
    ${Boost_LIBRARIES} )
