# 
# @brief    : custom mavlink msg, message id="227" name="VISION_ONE_NUM_GET"
# @time     : 2016/09/11
# @auhtor   : huang li long <huanglilongwk@outlook.com> 
#

std_msgs/Header header

# Get the number by vision in task (Mavros->Pix->GCS)
uint64 timestamp        # timestamp
uint8  loop_value       # loop number of current task but not 0, 1~5
uint8  num              # gotten number by vision
