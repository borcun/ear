#include "spdlog/spdlog.h"
#include "positioning.h"
#include "serial_service.h"
#include "gps.h"
#include "ssched.h"

int main() {
  FACE::ServiceScheduler ps_scheduler;
  FACE::ServiceScheduler pcs_scheduler;
  Positioning pos_1 {"pos-serv-1"}, pos_2 {"pos-serv-2"};
  GPS gps_1 {"gps-dev-1"};
  SerialService ser_serv_1 {"ser-serv-1"};
  FACE::TSS::Channel channel_1 {"channel-1"},
      channel_2 {"channel-2"},
      channel_3 {"channel-3"};

  if (!(channel_1.open() && channel_2.open() && channel_3.open())) {
      return -1;
  }

  channel_2.subscribe(channel_1);
  channel_3.subscribe(channel_1);

  gps_1.setPeriod(std::chrono::microseconds(100000));    // 1 sec
  gps_1.setIOService(&ser_serv_1);
  gps_1.setChannel(&channel_1);

  pos_1.setPeriod(std::chrono::microseconds(100000));    // 1 sec
  pos_1.setChannel(&channel_2);
  pos_2.setPeriod(std::chrono::microseconds(100000));    // 1 sec
  pos_2.setChannel(&channel_3);
  
  if (!ps_scheduler.addService(&gps_1)) { return -1; }
  if (!pcs_scheduler.addService(&pos_1)) { return -1; }
  if (!pcs_scheduler.addService(&pos_2)) { return -1; }

  spdlog::info("schedulers initialize");
  if (!ps_scheduler.init()) { return -1; }
  if (!pcs_scheduler.init()) { return -1; }
  
  spdlog::info("schedulers are running");
  if (!ps_scheduler.run()) { return -1; }
  usleep(500000);
  if (!pcs_scheduler.run()) { return -1; }

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  if (!pcs_scheduler.terminate()) { return -1; }
  if (!ps_scheduler.terminate()) { return -1; }
  
  spdlog::info("schedulers terminated");

  channel_1.close();
  channel_2.close();
  channel_3.close();
  
  return 0;
}
