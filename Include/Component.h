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

#ifndef COMPONENT_H
#define COMPONENT_H

#include "./Pointers.h"
#include "./util/Rectangle.h"
#include "./util/Dimension.h"
#include "./util/Point.h"
#include "./util/Insets.h"
#include "./util/Color.h"

namespace ui
{
	/**
	 * Basic Component.
	 * Defines basic functionality for all Components
	 * used in this Graphical User Interface ToolKit.
	 */
	class Component
	{
	public:
		/**
		 * Default constructor
		 */
		Component();

		/**
		 * Copy constructor.
		 * @param
		 *	rhs the Component from which to construct a new Component.
		 */
		Component(const Component& rhs);

		/**
		 * Assignment operator.
		 * @param
		 *	rhs the Component assigned to this object.
		 * @return
		 *	the new Component.
		 */
		Component& operator=(const Component& rhs);

		/**
		 * Destructor.
		 * This constructor is virtual so classes inheriting from
		 * Component can correctly free their memory.
		 */
		virtual ~Component();

		/**
		 * Swaps two Components.
		 * Guaranteed not to throw.
		 */
		void swap(Component& rhs) throw();

		/**
		 * Enables or disables this Component.
		 * Disabling the Component makes this Component
		 * ignore any user input (that is, mouse and key events
		 * generated by a user).
		 */
		virtual void setEnabled(bool enable);

		/**
		 * Returns whether or not this Component is enabled.
		 */
		bool isEnabled() const;

		/**
		 * Renders the Component invisible or visible.
		 * Default value for Components is visible, except
		 * the \a Frame. 
		 * @param
		 *	visible variable to render the widget visible (true) or invisible (false).
		 */
		void setVisible(bool visible);

		/**
		 * Method that returns the current visibility state
		 * of the current Component.
		 * @return
		 *	true if the Component is visible, false if it's invisible.
		 * @note
		 *	If an Component is set to invisible, noone of it's children
		 *	components are painted.
		 * @see
		 *	setVisible
		 */
		bool isVisible() const;

		/**
		 * Invalidates this Component.
		 * This forces the Component and it's parent
		 * to do a layout call.
		 */
		virtual void invalidate();

		/**
		 * Validates this Component.
		 */
		virtual void validate() const;

		/**
		 * Returns whether or not this Component is valid.
		 * If this returns true, that means all of it's children
		 * (in case it's an Container) are also valid.
		 * @return
		 *	true if the Component is valid, false otherwise.
		 */
		bool isValid() const;

		/**
		 * Sets the parent for this Component.
		 * Can be NULL (0) if no parent is present.
		 * @param
		 *	parent the Component to use as parent.
		 */
		void setParent(Component* parent);

		/**
		 * Returns the parent for this Component.
		 * @return
		 *	returns a pointer to this Components parent.
		 *	The parent might be NULL (0), in case the
		 *	Component is a root container (which has no parent).
		 */
		Component* getParent() const;

		/**
		 * Paint method called by the Component's parent. 
		 * Do not call this method manually, as it's used
		 * by the Component to paint itself (together with the
		 * look and feel manager - which is currently not implemented)
		 * @param
		 *	g Graphics reference used for painting.
		 */
		void paint(Graphics& g) const;

	protected:
		/**
		 * Custom Component painting.
		 * Overload to implement custom drawing.
		 * @param
		 *	g Graphics reference used for painting.
		 */
		virtual void paintComponent(Graphics& g) const;

		/**
		 * Paint this Components children.
		 * @param
		 *	g Graphics reference used for painting.
		 */
		virtual void paintChildren(Graphics& g) const;

		/**
		 * Paints this Components border, if one
		 * is present.
		 * @param
		 *	g Graphics reference used for painting.
		 */
		void paintBorder(Graphics& g) const;	

		/**
		 * This method paints a unique colored rectangle
		 * to the screen for use by the picking engine.
		 * You can override this method to do custom
		 * selection rendering, for example for pictures.
		 * @param
		 *	g Graphics reference used for painting.
		 */
		virtual void paintSelectionComponent(Graphics &g) const;

		/**
		 * Validate the Component tree.
		 * This validates this Components and all
		 * of it's children. Most likely by invoking
		 * their LayoutManagers.
		 */
		virtual void validateTree() const {};

	public:
		/**
		 * Returns the current foreground color
		 * for this Component.
		 * @return
		 *	Color object holding the color values.
		 * @see
		 *	Color
		 *	setForeground
		 */
		util::Paint* getForeground() const;

		/**
		 * Sets the Component's foreground color.
		 * @param
		 *	c Color object holding the color variables.
		 */
		void setForeground(util::Paint* c);

		/**
		 * Returns the current background color
		 * for this Component.
		 * @return
		 *	Color object holding the color values.
		 * @see
		 *	Color
		 *	setBackground
		 */
		util::Paint* getBackground() const;

		/**
		 * Sets the Component's background color.
		 * @param
		 *	c Color object holding the color variables.
		 */
		void setBackground(util::Paint* c);

		/**
		 * Sets the theme for this Component. The theme
		 * can be viewed as the View in MVC. It decides how
		 * this particular component is rendered.
		 * @param
		 *	theme New theme to be used by this Component.
		 */
		void setTheme(theme::ThemeComponent *theme);

		/**
		 * Reset all theme values by calling
		 * deinstallTheme and installTheme in succession.
		 */
		void resetTheme(); 

		/**
		 * Sets the theme name, this is the identifier used
		 * to decide which ThemeComponent to choose when requesting
		 * a theme.
		 * This is for internal use only, or if you're writing your
		 * own custom Components.
		 */
		void setThemeName(const std::string &name);

		/**
		 * Returns the theme name.
		 */
		const std::string & getThemeName() const;

		/**
		 * Returns the active theme.
		 */
		const theme::ThemeComponent* getTheme() const;

		/**
		 * Sets the Components location without modifying
		 * it's height and width.
		 * @param
		 *	x Component horizontal position.
		 * @param
		 *	y Component vertical position.
		 */
		void setLocation(int x, int y);

		/**
		 * Sets the Components relative location without modifying
		 * it's height and width. The relative location is the 
		 * location inside the Components Container (it's parent).
		 * @param
		 *	p Point containing the new x and y positions.
		 */
		void setLocation(const util::Point& p);

		/**
		 * Returns the current location as a Point.
		 * @return
		 *	Return the current location inside it's
		 *	container.
		 * @note
		 *	Note that this does not return the screen
		 *	location for this Component. To get the current
		 *	screenlocation, use getLocationOnScreen().
		 * @see
		 * getLocationOnScreen
		 */
		const util::Point getLocation() const;

		/**
		 * Returns the Component location in 
		 * screen coordinates.
		 * @note to get the coordinates relative to
		 * the Components Container, use getLocation.
		 * @see
		 * getLocation
		 */
		const util::Point getLocationOnScreen() const;

		/**
		 * Set all the Components Rectangle properties.
		 * @param
		 *	x Component horizontal position.
		 * @param
		 *	y Component vertical position.
		 * @param
		 *	width Component width.
		 * @param
		 *	height Component height.
		 */
		void setBounds(int x, int y, int width, int height);

		/**
		 * Set the new bounds for this Component.
		 * @param
		 *	rhs the Rectangle to use as dimension and position.
		 */
		void setBounds(const util::Rectangle& rhs);

		/**
		 * Returns the current Rectangle from
		 * this Component.
		 * @return
		 *	Rectangle holding the current position and size values.
		 * @see
		 *	Rectangle
		 */
		const util::Rectangle& getBounds() const;

		/**
		 * Returns the Components preferred size.
		 * @return
		 *	The preferredSize of this Component as Dimension.
		 * @note
		 *	The actual width and height of the Component might
		 *	differ from the preferredSize. Use getBounds to
		 *	receive the real values.
		 * @see
		 *	setPreferredSize
		 *	getBounds
		 *	setBounds
		 */
		virtual const util::Dimension& getPreferredSize() const;

		/**
		 * Sets the preferred size.
		 * The prefferedSize is a hint to the layoutmanager,
		 * which might or might not respect this hint.
		 * @param
		 *	d the preferredSize for this Component.
		 */
		void setPreferredSize(const util::Dimension& d);

		/**
		 * Sets the Components width and height without modifying
		 * it's location.
		 * @param
		 *	width Component width.
		 * @param
		 *	height Component height.
		 */
		void setSize(int width, int height);

		/**
		 * Sets the Components width and height without modifying
		 * it's location.
		 * @param
		 *	rhs new Component dimension.
		 */
		void setSize(const util::Dimension& rhs);

		/**
		 * Sets the depth for this Component. Different depths
		 * are used to paint popup menus and such. This allows
		 * us to use the normal Component hierarchy and still
		 * be able to do special painting for Components.
		 * @param
		 *	type the depth type to use for this Component.
		 * @see
		 *	ComponentDepth
		 */
		void setDepth(int type);

		/**
		 * Retreives the current Component depth.
		 * @return
		 *	returns the current depth.
		 */
		int getDepth() const;

		/**
		 * Component depth values.
		 * The actual float depth is
		 * 1/ComponentDepth.
		 */
		enum ComponentDepth
		{
			/**
			 * Depth for all normal Components.
			 */
			NORMAL = 8,
			/**
			 * Depth for normal modal Components
			 */
			NORMAL_MODAL = 4,

			/**
			 * Depth for popup Components.
			 */
			POPUP = 2,

			/**
			 * Depth for modal popup Components.
			 */
			POPUP_MODAL = 1
		};

		/**
		 * Wether the Component is a Container.
		 * @return
		 *	false
		 */
		virtual bool isContainer() const;

		/**
		 * Returns wether this Component is a Root level
		 * container.
		 * @return
		 *	true if this is a root container, false otherwise.
		 */
		virtual bool isRootContainer() const;

		/**
		 * Returns the Components children as a stl list object.
		 * @note this method will always return a list of size null,
		 * unless the Component is a Container.
		 * @see
		 *	Container
		 * @return
		 *	the componentList containing all the children.
		 */
		const ComponentList& getChildren() const;

		/**
		 * Enable or disable drawing of the Components border, if any.
		 * @param
		 *	enable true to paint the borders, false to ignore them.
		 * @note
		 *	this will only affect the visual aspect, not borders size calculation.
		 */
		void setBorderPainted(bool enable);

		/**
		 * Returns true if the border is painted.
		 * @return
		 *	true if the border is being painted, false otherwise.
		 */
		bool isBorderPainted() const;

		/**
		 * Check to see if the Component has a border.
		 * @return
		 *	true if the Component has a border, false otherwise.
		 */
		bool hasBorder() const;

		/**
		 * Replaces the Components border with the specified border.
		 * This also replaces the Components Insets with the borders Insets.
		 * @param
		 *	b border to use for this Component.
		 * @see Insets, Border
		 */
		void setBorder(border::Border* b);

		/**
		 * Returns the active border.
		 */
		border::Border * getBorder() const;

		/**
		 * Sets the Insets for the Component.
		 * @note
		 *	Note that these might be replaces when a border is
		 *	added to the Component.
		 * @see
		 *	Insets
		 * @param
		 *	i the inset to be used as new inset.
		 */
		void setInsets(const util::Insets& i);

		/**
		 * Returns the current Components Insets.
		 * @return
		 *	The Components current Insets.
		 */
		const util::Insets& getInsets() const;

		/**
		 * Sets the Font for this Component.
		 * @param
		 *	font Font to be used for this Component.
		 * @see
		 *	Font Character
		 */
		void setFont(Font* font);

		/**
		 * Returns the current Font for this Component.
		 * @return
		 *	the Font used by this Component.
		 */
		Font* getFont() const;

		/**
		 * Constants for general use in Components.
		 */
		enum CONSTANTS
		{
			/**
			 * Defines left.
			 */
			LEFT,
			/**
			 * Defines right.
			 */
			RIGHT,
			/**
			 * Defines center.
			 */
			CENTER,

			HORIZONTAL,

			VERTICAL
		};

		/**
		 * Receives a MouseEvent for this Component and forwards
		 * it to all registered MouseListeners.
		 * @param
		 *	e the MouseEvent to process.
		 */
		void processMouseEvent(const event::MouseEvent& e);
		 
		/**
		 * Check wether the Component has a MouseListener.
		 * @return
		 *	true if the Component has a MouseListener, false otherwise.
		 */
		bool hasMouseListener() const;

		/**
		 * Add a event::MouseListener to the Component.
		 * @param
		 *	l MouseListener to be registered for the Component.
		 */
		void addMouseListener(event::MouseListener* l);

		/**
		 * Remove the selected MouseListener.
		 * @param
		 *	l the MouseListener to be removed from the Component.
		 */
		void removeMouseListener(event::MouseListener* l);

		/**
		 * Removes all MouseListeners for this Component.
		 */
		void removeMouseListeners();

		/**
		 * Check to see if the Component has focus.
		 * @return
		 *	true if the Component has focus, false otherwise.
		 */
		bool hasFocus() const;

		/**
		 * Set the focus to the Component.
		 * @param
		 *	enable true if the Component is in focus, false to loose focus.
		 */
		void setFocus(bool enable);

		/**
		 * Process the focus event and forward it to the specified component.
		 * @param
		 *	e the FocusEvent to be processed by this Component.
		 */
		void processFocusEvent(const event::FocusEvent& e);

		/**
		 * Add a event::FocusListener to the Component.
		 * @param
		 *	l FocusListener to be registered for the Component.
		 */
		void addFocusListener(event::FocusListener* l);
		
		/**
		 * Remove the selected FocusListener
		 * @param
		 *	l the FocusListener to be removed from this Component.
		 */
		void removeFocusListener(event::FocusListener* l);

		/**
		 * Removes all FocusListeners from this Component.
		 */
		void removeFocusListeners();

		/**
		 * Returns all FocusListeners registered by this Component.
		 * @return
		 *	return a list of all registered FocusListeners.
		 */
		const event::FocusListenerList getFocusListeners() const;

		/**
		 * Check wether the Component has a FocusListener.
		 * @return
		 *	true if the Component has a FocusListener, false otherwise.
		 */
		bool hasFocusListener() const;

		/**
		 * Returns wether or not this Component can be
		 * a permanent focus owner. This is true by default,
		 * except for things like MenuItems, where a menu is
		 * the permanent focus owner and a menuitem merely a 
		 * focus owner.
		 */
		virtual bool canHoldPermanentFocus() const;

		/**
		 * Add a event::KeyListener to the Component.
		 * @param
		 *	l KeyListener to be registered for the Component.
		 */
		void addKeyListener(event::KeyListener* l);
		
		/**
		 * Remove the selected KeyListener
		 * @param
		 *	l the KeyListener to be removed from the Component.
		 */
		void removeKeyListener(event::KeyListener* l);

		/**
		 * Removes all KeyListeners from this Component.
		 */
		void removeKeyListeners();

		/**
		 * Returns all KeyListeners registered by this Component.
		 * @return
		 *	returns a list of all registered KeyListeners for this Component.
		 */
		const event::KeyListenerList getKeyListeners() const;

		/**
		 * Check wether the Component has a KeyListener.
		 * @return
		 *	true if the Component has a KeyListener, false otherwise.
		 */
		bool hasKeyListener() const;

		/**
		 * Forward the KeyEvent to all registered Listeners.
		 * @param
		 *	e the KeyEvent to be processed by this Component.	
		 */
		void processKeyEvent(const event::KeyEvent& e);

		/**
		 * Forward the PropertyEvent to all registered Listeners.
		 * @param
		 *	e the PropertyEvent to be processed by this Component.	
		 */
		void processPropertyEvent(const event::PropertyEvent& e);

		/**
		 * Add a event::PropertyListener to the Component.
		 * @param
		 *	l PropertyListener to be registered for the Component.
		 */
		void addPropertyListener(event::PropertyListener* l);
		
		/**
		 * Remove the selected PropertyListener
		 * @param
		 *	l the PropertyListener to be removed from the Component.
		 */
		void removePropertyListener(event::PropertyListener* l);

		/**
		 * Removes all KeyListeners from this Component.
		 */
		void removePropertyListeners();

		/**
		 * Returns all PropertyListeners registered by this Component.
		 * @return
		 *	returns a list of all registered PropertyListeners for this Component.
		 */
		const event::PropertyListenerList getPropertyListeners() const;

		/**
		 * Check wether the Component has a PropertyListener.
		 * @return
		 *	true if the Component has a PropertyListener, false otherwise.
		 */
		bool hasPropertyListener() const;

		/**
		 * Update, for time based motion.
		 * @param
		 *	deltaTime time between two sequential frames. This can be 
		 *	used for calculating frame rate independant motion.
		 */
		virtual void updateComponent(float deltaTime);

		/**
		 * Add an interpolator to this Component.
		 * @see Interpolator
		 */
		void addInterpolator(util::Interpolator* i);

		/**
		 * Remove a specified interpolator from this Component.
		 * @param
		 *	i the Interpolator to be removed from this Component.
		 */
		void removeInterpolator(util::Interpolator* i);

		/**
		 * Remove all interpolators from this Component.
		 */
		void removeInterpolators();

		/**
		 * Sets the transparency for this Component and it's
		 * children.
		 * Note that the transparency can range from 0.0 to 1.0.
		 * @param
		 *	f Transparency value for this Component and it's children.
		 */
		void setTransparency(float f);

		/**
		 * Returns the current transparency level for this
		 * Component and it's children.
		 * @return
		 *	the current transparency value.
		 */
		float getTransparency() const;

		/**
		 * Sets the rotation for this Component in
		 * degrees. Rotation is clockwise.
		 * @param
		 *	r The degrees by which to rotate.
		 */
		void setRotation(float r);

		/**
		 * Returns the rotation for this Component
		 * in degrees.
		 * @see setRotation
		 */
		float getRotation() const;

	private:
		bool visible, borderPainted, focus,enabled;

		mutable bool valid;
		
		/**
		 * Transparency value for this Component and
		 * all of it's children.
		 */
		float					transparency;

		/**
		 * List that holds all registered mouse listeners.
		 */
		event::MouseListenerList mouseListeners;

		/**
		 * List that holds all registered focus listeners.
		 */
		event::FocusListenerList focusListeners;

		/**
		 * List that holds all registered key listeners.
		 */
		event::KeyListenerList keyListeners;

		/**
		 * List that holds all registered interpolators.
		 */
		util::InterpolatorList interpolators;

		/**
		 * List that holds all registered property listeners.
		 */
		event::PropertyListenerList propertyListeners;

		/**
		 * A pointer to the parent of this class.
		 * Should only be NULL if this is a root frame.
		 */
		Component*			parent;

		/**
		 * This Components background color.
		 */
		util::Paint					*background;

		/**
		 * This Components foreground color.
		 */
		util::Paint					*foreground;

		/**
		 * This Components size and location.
		 */
		util::Rectangle				rec;

		/**
		 * This Components border
		 */
		border::Border*				border;

		/**
		 * This Components Insets.
		 */
		util::Insets				insets;

		/**
		 * An integer pointing to the Font.
		 */
		std::size_t						font;

		/**
		 * The theme component.
		 */
		theme::ThemeComponent		*theme;

		/**
		 * The the theme identifier.
		 */
		std::string				name;

		float				rotation;

		unsigned int	displayList;

		mutable bool			isDisplayListCompiled;

	protected:
		/**
		 * Depth value for this Component.
		 */
		float					depth;

		/**
		 * A container containing Components.
		 * we already declare this here, so it's
		 * available to every Component.
		 */
		ComponentList		componentList;

		/**
		 * Cache values for the Dimension so
		 * we do not have to recalculate it
		 * at every frame (although that works fine too). 
		 * This variable is made mutable so we can change it
		 * in const members. As preferredSize is a cache value,
		 * it does not affect the object state towards the user.
		 */
		mutable util::Dimension				preferredSize;
	};
}
#endif