# 
# @brief    : custom mavlink msg, message id="223" name="YAW_SP_CALCULATED"
# @time     : 2016/09/11
# @auhtor   : huang li long <huanglilongwk@outlook.com> 
# 

std_msgs/Header header

# A yaw setpoint calculated by SBC from FIXED_TARGET_POSITION message (Mavros->Pix->GCS)
uint64  timestamp        # timestamp
float32 yaw_sp           # the calculated yaw set point, in rad (-pi ... pi)
