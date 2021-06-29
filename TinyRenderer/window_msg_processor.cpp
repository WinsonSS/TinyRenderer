#include "window_msg_processor.h"
#include <cstdio>

WindowMsgProcessor::WindowMsgProcessor() : msg_(new MSG()), have_msg_(false) {}


WindowMsgProcessor::~WindowMsgProcessor()
{
	delete msg_;
}


bool WindowMsgProcessor::Update()
{
	have_msg_ = PeekMessage(msg_, nullptr, 0, 0, PM_REMOVE);
	if (have_msg_ && msg_->message == WM_QUIT)
		return false;
	if (have_msg_)
	{
		TranslateMessage(msg_);
		DispatchMessage(msg_);
	}
	return have_msg_;
}


MSG* WindowMsgProcessor::msg()
{
	return msg_;
}


bool WindowMsgProcessor::ShouldQuit()
{
	return have_msg_ && msg_->message == WM_QUIT;
}

