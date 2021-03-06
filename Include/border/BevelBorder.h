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

#ifndef BEVELBORDER_H
#define BEVELBORDER_H

#include "Border.h"
#include "../util/Color.h"

namespace ui
{
	namespace border
	{
		/**
		 * A classic bevel border, which has two different states.
		 * Raised or Lowered, indicating a unpressed component, or
		 * pressed.
		 */
		class BevelBorder : public Border
		{
			public:
				enum beveltypes
				{
					RAISED,
					LOWERED
				};
				/**
				 * Create a default, raised bevel border.
				 */
				BevelBorder();

				/**
				 * Create a border with the given bevel state.
				 * @param
				 *	type beveltype to use.
				 */
				BevelBorder(int type);

				/**
				 * Copy constructor.
				 */
				BevelBorder(const BevelBorder& rhs);

				/**
				 * Assignment operator.
				 */ 
				BevelBorder& operator=(const BevelBorder &rhs);

				/**
				 * Swaps the contents of this Border with another.
				 */
				void swap(BevelBorder& rhs) throw();

				/**
				 * Paint the border.
				 */
				void paintBorder(const Component* component, Graphics& g, int x, int y, int w, int h) const;

				/**
				 * Returns the Insets of this border.
				 * The insets are the space requirements
				 * for this border.
				 * @see Insets
				 * @return
				 *	The insets needed for this Border.
				 */
				const util::Insets getBorderInsets() const;

				/**
				 * Change the beveltype.
				 * @param
				 *	type the beveltype to use for this border. 
				 */
				void setType(int type);

				/**
				 * Return the bevel type of this object.
				 * Can be either raised or lowered.
				 * @return
				 *	the border type.
				 */
				int getType() const;
			private:
				/**
				 * Paint a raised border.
				 */
				void paintRaisedBorder(Graphics& g, int x, int y, int w, int h) const;

				/**
				 * Paint a lowered border.
				 */
				void paintLoweredBorder(Graphics& g, int x, int y, int w, int h) const;

				/**
				 * Indicate if this border is raised.
				 */
				int isRaised;
				util::Color raisedShadow;
				util::Color raisedHighlight;
				util::Color loweredShadow;
				util::Color loweredHighlight;
		};
	}
}

#endif