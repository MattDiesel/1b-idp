#include "util/tracker.h"
#include "subroutines.h"


void q2_deliver_d2d3(Robot& r) {
	Tracker::instance()->logPose(0.2, -0.8, 0);
	r.drive.move({forward: 1, steer: 0.5});

	delay(1000);
	waitForLine(r, negate { LineSensors::Reading::NONE });
	std::cout << "Departed conveyor and found line" << std::endl;

	followUntil(r, 0.30, until_junction);
	checkpoint(r, "Junction Before Ramp");
	turnAtJunction(r, 1);
	checkpoint(r, "Looking up ramp");

	followUntil(r, 999999, until_junction); // ramps takes forever, so just drop the timeout
	checkpoint(r, "Top of ramp");

	turnAtJunction(r, 1);
	checkpoint(r, "Looking along plateau");

	followUntil(r, 0.86, until_junction);
	checkpoint(r, "At plateau center");

	followUntil(r, 0.86, until_junction);
	r.drive.straight(0.1).wait();
	checkpoint(r, "At delivery nexus");

	while(r.courier.volume() != 0) {
		if(r.courier.egg(0) == EGG_BROWN) {
			// curve left, until we intersect the line
			r.drive.move({forward: 0.35, steer: 0.65});
			Timeout(r.drive.timeForTurn(45, 0.65)).wait();

			while(r.ls.read().lsc);
			while(!r.ls.read().lsc);
			r.drive.stop();

			// run until the limit switches go
			dropEggs(r, r.courier.egg(1) == EGG_BROWN ? 2 : 1);

			// undo the curved motion
			r.drive.move({forward: -0.35, steer: -0.65});
			Timeout(r.drive.timeForTurn(-45, 0.65)).wait();
			while(r.ls.read().lsc);
			while(!r.ls.read().lsc);
			r.drive.stop();
		}
		else {
			dropEggs(r, 1);
		}
	}

	r.drive.straight(-0.3).wait();
	std::cout << "At delivery nexus" << std::endl;
}
