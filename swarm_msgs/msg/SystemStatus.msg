Header header

# Infra Status
uint32 INFRA_INACTIVE = 0
uint32 INFRA_AP_CONNECTED = 1
uint32 INFRA_ODOM_READY = 2
uint32 INFRA_AP_EKF_READY = 3
uint32 INFRA_ARMED = 4

# Navigation Status
string NAV_IDLE = IDLE
string NAV_SEARCH = SEARCH
string NAV_APPROACH = APPROACH
string NAV_ROOT_TRACK = ROOT_TRACK
string NAV_PURE_TRACK = PURE_TRACK
string NAV_HOVER = HOVER
string NAV_POSHOLD = POSHOLD

# Ardupilot Status
string AP_STABILIZE = STABILIZE
string AP_ACRO = ACRO
string AP_ALT_HOLD = ALT_HOLD
string AP_AUTO = AUTO
string AP_GUIDED = GUIDED
string AP_LOITER = LOITER
string AP_RTL = RTL
string AP_CIRCLE = CIRCLE
string AP_POSITION = POSITION
string AP_LAND = LAND
string AP_OF_LOITER = OF_LOITER
string AP_DRIFT = DRIFT
string AP_SPORT = SPORT
string AP_FLIP = FLIP
string AP_AUTOTUNE = AUTOTUNE
string AP_POSHOLD = POSHOLD
string AP_BRAKE = BRAKE
string AP_THROW = THROW
string AP_AVOID_ADSB = AVOID_ADSB
string AP_GUIDED_NOGPS = GUIDED_NOGPS

uint32 drone_id
uint32 infra_status
string nav_status
string ap_status