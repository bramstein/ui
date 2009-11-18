/*
 * Copyright (c) 2003-2006, Bram Stein
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 *  2. Redistributions in binary form must reproduce the above copyright 
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution. 
 *  3. The name of the author may not be used to endorse or promote products 
 *     derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO 
 * EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "./Button.h"
#include "../event/MouseEvent.h"

namespace ui
{
	Button::Button(const std::string &label)
	{
		init(0,label);
	}

	Button::Button(Icon *icon, const std::string &label)
	{
		init(icon,label);
	}

	void Button::init(Icon *icon,const std::string &label)
	{
		setThemeName("Button");
		setDefaultIcon(icon);
		addMouseListener(this);
		addFocusListener(this);
		setText(label);
	}

	void Button::mousePressed(const event::MouseEvent& e)
	{
		if(e.getButton() == event::MouseEvent::MOUSE_BUTTON2)
		{
			setSelected(true);
		}
	}

	void Button::mouseReleased(const event::MouseEvent& e)
	{
		if(e.getButton() == event::MouseEvent::MOUSE_BUTTON2)
		{
			setSelected(false);
		}
	}

	void Button::focusGained(const event::FocusEvent& e)
	{
	//	setFocusPainted(true);
	}

	void Button::focusLost(const event::FocusEvent& e)
	{
	//	setFocusPainted(false);
	}
}