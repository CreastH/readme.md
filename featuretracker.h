#pragma once

#include <opencv2/core/utility.hpp>
#include"videoprocessor.h"
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

class VisualTracker :public FrameProcessor {
	Ptr<Tracker> tracker;
	Rect2d box;
	bool reset;

public:
	//constructor specifying the tracker to be used 
	VisualTracker(Ptr<Tracker> tracker) :reset(true), tracker(tracker) {}

	//set the bounding box to initiate tracking
	void setBoundingBox(const Rect2d& bb) {
		box = bb;
		if (box.width == 0 || box.height == 0) {
			cout << "There is no more frame or some ERROR!!" << endl;
			system("pause");
		}
		else
			reset = true;
	}

	//callback processing method
	void process(Mat &frame, Mat &output) {
		if (reset) {//new tracking session
			reset = false;
			tracker->init(frame, box);  //this box can be init by onMouse class
		}
		else {
			//updata the target`s position
			tracker->update(frame, box);
		}

		//draw bounding box on current frame
		frame.copyTo(output);
		rectangle(output, box, Scalar(255, 255, 255), 2);
	}
};
