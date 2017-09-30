# 
# @brief    : custom mavlink msg, message id="225" name="TASK_STATUS_MONITOR"
# @time     : 2016/09/11
# @auhtor   : huang li long <huanglilongwk@outlook.com> 
# 

std_msgs/Header header

# Return current task statue and taget point (Mavros->Pix->GCS)
uint64  timestamp           # timestamp
uint8   num_odd_even        # 0, 1 or 2 represent spray all number, odd number or even number
uint8   task_status         # task status NO. about Task State Machine, 0~16~30
uint8   loop_value          # loop number of current task, 0~5
float64 target_lat          # target latitude, in deg
float64 target_lon          # target longitude, in deg
float32 target_alt          # target altitude, in m
