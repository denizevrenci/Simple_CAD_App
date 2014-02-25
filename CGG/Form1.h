#pragma once

namespace CGG{	

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>

	public ref class Form1 : public System::Windows::Forms::Form{
	private:

		/******************************************************************
		*****************User-Defined Variables - Start********************
		*******************************************************************/

		// Graphics Variables - Start
		// Pens and brushes - Start
		Pen^ pen_0; // screen objects
		Pen^ pen_1; // pane frames
		Pen^ pen_2; // x axis
		Pen^ pen_3; // y axis
		Pen^ pen_4; // z axis
		Pen^ pen_5; // defining polygon
		Pen^ pen_6; // cubic spline derivatives
		System::Drawing::Drawing2D::LinearGradientBrush^ brush_0; // Background. Previously SolidBrush was used
		// Pens and brushes - End
		PaintEventArgs^ pe;
		System::UInt32 pen_color;
		System::UInt32 brush_color_0;
		System::UInt32 brush_color_1;
		array<Color>^ brush_colors;
		System::Boolean paint_lock;
		System::Boolean preview_lock;
		System::Drawing::Size form_cli_difference;
		System::Drawing::Point axes_origin;
		System::Boolean resample;
		// Graphics Variables - End

		// Form Variables - Start
		array<System::Windows::Forms::Panel^>^ panelarray;
		array<System::Byte>^ panel_specifier;  // used in the case that a panel is used to take input to multiple variables. Specifies which variable will take the input.
			/* panel_specifier list
				0 - color change textboxes
			*/
		array<System::Byte>^ panel_controller; // used in the case that an input field is required to be muted.
			/* panel_controller list
				0 - color change textboxes
			*/
		System::Byte activepanel;		
		// Form Variables - End

		// Input Variables - Start
		System::Boolean drag_control;
		System::Boolean click_control;
		System::Drawing::Point prev_location;
		System::Drawing::Point delta;
		System::Drawing::Point radius;
		vector3D point_argument;
		System::Boolean click_key_switch; // specifies whether a mouse click will input data to the created object
		System::Boolean click_permit; // specifies whether the mouse clicks are enabled on the object creation state
		// Input Variables - End

		// System Variables - Start
		Screen_Object^ object_list_header;
		Screen_Object^ selected_object;
		System::Double global_scale;
		System::Double global_shift_x; // represents the origin of the 3D space on the screen
		System::Double global_shift_y;
		System::Double construction_depth;
		vector3D view_x;
		vector3D view_y;
		vector3D view_z;
		vector3D rotator;
		vector3D temp_vector_0;
		vector3D temp_vector_1;
		System::Double object_rotation;
		System::Double delta_theta;			
		System::Byte object_creation_state; 
			/* specifies the current state of object creation mechanism
			   ("*" at the end represents vector3D input)
				  0 - creation stopped
				  1 - line phase 1* (1st point)
				  2 - line phase 2* (2nd point)
				  3 - polyline phase 1* (1st point)
				  4 - polyline phase 2* (2nd point)
				  5 - polyline phase 3* (the rest of the points)
				  6 - polygon phase 1 (number of sides)
				  7 - polygon phase 2 (rotation angle)
				  8 - polygon phase 3 (size)
				  9 - polygon phase 4* (center)
				 10 - circle phase 1 (radius)
				 11 - circle phase 2* (center)
				 12 - ellipse phase 1 (major-axis size)
				 13 - ellipse phase 2 (minor-axis size)
				 14 - ellipse phase 3 (rotation)
				 15 - ellipse phase 4* (center)
				 16 - bezier phase 1* (1st point)
				 17 - bezier phase 2* (2nd point)
				 18 - bezier phase 3* (the rest of the points)
				 19 - cubic spline phase 1 (end conditions)
				 20 - cubic spline phase 2* (1st point)
				 21 - cubic spline phase 3* (1st point derivative)
				 22 - cubic spline phase 4* (2nd point)
				 23 - cubic spline phase 5* (the rest of the points)
				 24 - cubic spline phase 6* (end point derivative)
				 25 - parabola phase 1* (directrix 1st point)
				 26 - parabola phase 2* (directrix 2nd point)
				 27 - parabola phase 3* (focus)
				 28 - parabola phase 4 (first end x)
				 29 - parabola phase 5 (second end x)
				 30 - circular arc phase 1*
				 31 - circular arc phase 2*
				 32 - circular arc phase 3*
				 33 - bspline phase 1 (mode selection)
				 34 - bspline phase 2* (1st point)
				 35 - bspline phase 3* (2nd point)
				 36 - bspline phase 4* (the rest of the points)
				 37 - bspline phase 5 (order control)
				 38 - mesh phase 1* (1st point)
				 39 - mesh phase 2* (2nd point)
				 40 - mesh phase 3* (the rest of the points)
				 41 - mesh phase 4* (1st point on 2nd dimension)
				 42 - mesh phase 5* (the rest of the points on 2nd dimension)
				 43 - bilinear surface phase 1* (1st point)
				 44 - bilinear surface phase 2* (2nd point)
				 45 - bilinear surface phase 3* (3rd point)
				 46 - bilinear surface phase 4* (4th point)
				 47 - bezier surface phase 1* (1st point)
				 48 - bezier surface phase 2* (2nd point)
				 49 - bezier surface phase 3* (the rest of the points)
				 50 - bezier surface phase 4* (1st point on 2nd dimension)
				 51 - bezier surface phase 5* (the rest of the points on 2nd dimension)
				 52 - bspline surface phase 1 (mode selection)
				 53 - bspline surface phase 2* (1st point)
				 54 - bspline surface phase 3* (2nd point)
				 55 - bspline surface phase 4* (the rest of the points)
				 56 - bspline surface phase 5* (1st point on 2nd dimension)
				 57 - bspline surface phase 6* (the rest of the points on 2nd dimension)
				 58 - bspline surface phase 7 (order_0 control)
				 59 - bspline surface phase 8 (order_1 control)
				 60 - bicubic surface phase 1 (1st point)
				 64 - bicubic surface phase 5 (1st point derivative 1)
				 68 - bicubic surface phase 9 (1st point derivative 2)
				 72 - bicubic surface phase 13 (1st point twist)
				 76 - hyperbola phase 1* (origin)
				 77 - hyperbola phase 2* (first asymptote)
				 78 - hyperbola phase 3* (second asymptote)
				 79 - hyperbola phase 4 (asymptotic behaviour scale)
				 80 - hyperbola phase 5 (first end y)
				 81 - hyperbola phase 6 (second end y)
				255 - final state for arbitrarily long objects
			*/
		System::Byte object_modification_state;
			/* specifies the current state of object modification mechanism
				  0 - modification stopped
				  1 - object deletion
				  2 - object color change phase 1 (selection)
				  3 - object color change phase 2 (color change)
				  4 - object shift phase 1 (selection)
				  5 - object shift phase 2 (shift)
				  6 - object scale phase 1 (selection)
				  7 - object scale phase 2 (origin)
				  8 - object scale phase 3 (scale)
				  9 - object rotate phase 1 (selection)
				 10 - object rotate phase 2 (first point on axis)
				 11 - object rotate phase 3 (second point on axis)
				 12 - object rotate phase 4 (rotate)
			*/
		// System Variables - End

		/******************************************************************
		******************User-Defined Variables - End*********************
		*******************************************************************/

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  lineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  conicSectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  circleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ellipseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  modifyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  parabolaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hyperbolaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cubicSplineToolStripMenuItem;	 
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  backgroundColorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  penColorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  polylineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  polylineStringToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  polygonToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  exitProgramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  shiftToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  scaleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rotateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteToolStripMenuItem;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  viewPlaneToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  changeColorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bezierCurveToolStripMenuItem;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel4;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::ToolStripMenuItem^  topViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  frontViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rightViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bottomViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  backViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  leftViewToolStripMenuItem;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::ToolStripMenuItem^  isometricViewToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::ToolStripMenuItem^  circularArcToolStripMenuItem;
	private: System::Windows::Forms::Panel^  panel6;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::ToolStripMenuItem^  generateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bilinearSurfaceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bicubicSurfaceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  beziérSurfaceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bSplineSurfaceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  meshToolStripMenuItem;
	private: System::Windows::Forms::Panel^  panel7;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Panel^  panel8;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::ToolStripMenuItem^  bSplineToolStripMenuItem;

	public:
		Form1(void){
			InitializeComponent();
			InitializeColors();
			InitializeAll();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1(){
			if (components){
				delete components;
			}
			ClearColors();
			ClearAll();
		}

	protected:
		   virtual void OnPaint(PaintEventArgs^ pe) override
		   {
				// Redraw the screen content when the form is repainted.

				// Static Components
				pe->Graphics->FillRectangle(brush_0, PANE_LEFT, PANE_TOP, PANE_WIDTH, PANE_HEIGHT);
				pe->Graphics->DrawRectangle(pen_1, PANE_LEFT, PANE_TOP, PANE_WIDTH, PANE_HEIGHT);
					
				// Screen Objects
				Screen_Object^ temporary_object_handle = object_list_header->GetNext();
				while(temporary_object_handle != object_list_header){
					DrawObject(temporary_object_handle);
					temporary_object_handle = temporary_object_handle->GetNext();
				}

				// Axes
				pe->Graphics->DrawLine(pen_2, axes_origin + XFormAxesto2D(vector3D(1, 0, 0) * 0.084), axes_origin + XFormAxesto2D(vector3D(1, 0, 0)));
				pe->Graphics->DrawLine(pen_3, axes_origin + XFormAxesto2D(vector3D(0, 1, 0) * 0.084), axes_origin + XFormAxesto2D(vector3D(0, 1, 0)));
				pe->Graphics->DrawLine(pen_4, axes_origin + XFormAxesto2D(vector3D(0, 0, 1) * 0.084), axes_origin + XFormAxesto2D(vector3D(0, 0, 1)));
		   }

	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


	#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->penColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->backgroundColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewPlaneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->topViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->frontViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rightViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bottomViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->backViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->leftViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->isometricViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->polylineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->polylineStringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->polygonToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->conicSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circularArcToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ellipseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->parabolaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hyperbolaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cubicSplineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bezierCurveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bSplineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->generateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->meshToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bilinearSurfaceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bicubicSurfaceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->beziérSurfaceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bSplineSurfaceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->modifyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->shiftToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->scaleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rotateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel3 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel4 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel6->SuspendLayout();
			this->panel7->SuspendLayout();
			this->panel8->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->fileToolStripMenuItem, 
				this->optionsToolStripMenuItem, this->toolStripMenuItem1, this->generateToolStripMenuItem, this->modifyToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(894, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"Menu";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->newToolStripMenuItem, 
				this->toolStripSeparator2, this->exitProgramToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(98, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::newToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->AutoSize = false;
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(95, 6);
			// 
			// exitProgramToolStripMenuItem
			// 
			this->exitProgramToolStripMenuItem->Name = L"exitProgramToolStripMenuItem";
			this->exitProgramToolStripMenuItem->Size = System::Drawing::Size(98, 22);
			this->exitProgramToolStripMenuItem->Text = L"Exit";
			this->exitProgramToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitProgramToolStripMenuItem_Click);
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->penColorToolStripMenuItem, 
				this->changeColorToolStripMenuItem, this->backgroundColorToolStripMenuItem, this->viewPlaneToolStripMenuItem});
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->optionsToolStripMenuItem->Text = L"View";
			// 
			// penColorToolStripMenuItem
			// 
			this->penColorToolStripMenuItem->Name = L"penColorToolStripMenuItem";
			this->penColorToolStripMenuItem->Size = System::Drawing::Size(170, 22);
			this->penColorToolStripMenuItem->Text = L"Set Color";
			this->penColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::penColorToolStripMenuItem_Click);
			// 
			// changeColorToolStripMenuItem
			// 
			this->changeColorToolStripMenuItem->Name = L"changeColorToolStripMenuItem";
			this->changeColorToolStripMenuItem->Size = System::Drawing::Size(170, 22);
			this->changeColorToolStripMenuItem->Text = L"Change Color";
			this->changeColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::changeColorToolStripMenuItem_Click);
			// 
			// backgroundColorToolStripMenuItem
			// 
			this->backgroundColorToolStripMenuItem->Name = L"backgroundColorToolStripMenuItem";
			this->backgroundColorToolStripMenuItem->Size = System::Drawing::Size(170, 22);
			this->backgroundColorToolStripMenuItem->Text = L"Background Color";
			this->backgroundColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::backgroundColorToolStripMenuItem_Click);
			// 
			// viewPlaneToolStripMenuItem
			// 
			this->viewPlaneToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->topViewToolStripMenuItem, 
				this->frontViewToolStripMenuItem, this->rightViewToolStripMenuItem, this->bottomViewToolStripMenuItem, this->backViewToolStripMenuItem, 
				this->leftViewToolStripMenuItem, this->isometricViewToolStripMenuItem});
			this->viewPlaneToolStripMenuItem->Name = L"viewPlaneToolStripMenuItem";
			this->viewPlaneToolStripMenuItem->Size = System::Drawing::Size(170, 22);
			this->viewPlaneToolStripMenuItem->Text = L"Display View";
			// 
			// topViewToolStripMenuItem
			// 
			this->topViewToolStripMenuItem->Name = L"topViewToolStripMenuItem";
			this->topViewToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->topViewToolStripMenuItem->Text = L"Top View";
			this->topViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::topViewToolStripMenuItem_Click);
			// 
			// frontViewToolStripMenuItem
			// 
			this->frontViewToolStripMenuItem->Name = L"frontViewToolStripMenuItem";
			this->frontViewToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->frontViewToolStripMenuItem->Text = L"Front View";
			this->frontViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::frontViewToolStripMenuItem_Click);
			// 
			// rightViewToolStripMenuItem
			// 
			this->rightViewToolStripMenuItem->Name = L"rightViewToolStripMenuItem";
			this->rightViewToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->rightViewToolStripMenuItem->Text = L"Right View";
			this->rightViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::rightViewToolStripMenuItem_Click);
			// 
			// bottomViewToolStripMenuItem
			// 
			this->bottomViewToolStripMenuItem->Name = L"bottomViewToolStripMenuItem";
			this->bottomViewToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->bottomViewToolStripMenuItem->Text = L"Bottom View";
			this->bottomViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bottomViewToolStripMenuItem_Click);
			// 
			// backViewToolStripMenuItem
			// 
			this->backViewToolStripMenuItem->Name = L"backViewToolStripMenuItem";
			this->backViewToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->backViewToolStripMenuItem->Text = L"Back View";
			this->backViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::backViewToolStripMenuItem_Click);
			// 
			// leftViewToolStripMenuItem
			// 
			this->leftViewToolStripMenuItem->Name = L"leftViewToolStripMenuItem";
			this->leftViewToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->leftViewToolStripMenuItem->Text = L"Left View";
			this->leftViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::leftViewToolStripMenuItem_Click);
			// 
			// isometricViewToolStripMenuItem
			// 
			this->isometricViewToolStripMenuItem->Name = L"isometricViewToolStripMenuItem";
			this->isometricViewToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->isometricViewToolStripMenuItem->Text = L"Isometric View";
			this->isometricViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::isometricViewToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->lineToolStripMenuItem, 
				this->polylineToolStripMenuItem, this->conicSectionToolStripMenuItem, this->cubicSplineToolStripMenuItem, this->bezierCurveToolStripMenuItem, 
				this->bSplineToolStripMenuItem});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(46, 20);
			this->toolStripMenuItem1->Text = L"Draw";
			// 
			// lineToolStripMenuItem
			// 
			this->lineToolStripMenuItem->Name = L"lineToolStripMenuItem";
			this->lineToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->lineToolStripMenuItem->Text = L"Line";
			this->lineToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::lineToolStripMenuItem_Click);
			// 
			// polylineToolStripMenuItem
			// 
			this->polylineToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->polylineStringToolStripMenuItem, 
				this->polygonToolStripMenuItem});
			this->polylineToolStripMenuItem->Name = L"polylineToolStripMenuItem";
			this->polylineToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->polylineToolStripMenuItem->Text = L"Polyline";
			// 
			// polylineStringToolStripMenuItem
			// 
			this->polylineStringToolStripMenuItem->Name = L"polylineStringToolStripMenuItem";
			this->polylineStringToolStripMenuItem->Size = System::Drawing::Size(150, 22);
			this->polylineStringToolStripMenuItem->Text = L"Polyline String";
			this->polylineStringToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::polylineStringToolStripMenuItem_Click);
			// 
			// polygonToolStripMenuItem
			// 
			this->polygonToolStripMenuItem->Name = L"polygonToolStripMenuItem";
			this->polygonToolStripMenuItem->Size = System::Drawing::Size(150, 22);
			this->polygonToolStripMenuItem->Text = L"Polygon";
			this->polygonToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::polygonToolStripMenuItem_Click);
			// 
			// conicSectionToolStripMenuItem
			// 
			this->conicSectionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->circleToolStripMenuItem, 
				this->circularArcToolStripMenuItem, this->ellipseToolStripMenuItem, this->parabolaToolStripMenuItem, this->hyperbolaToolStripMenuItem});
			this->conicSectionToolStripMenuItem->Name = L"conicSectionToolStripMenuItem";
			this->conicSectionToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->conicSectionToolStripMenuItem->Text = L"Conic Section";
			// 
			// circleToolStripMenuItem
			// 
			this->circleToolStripMenuItem->Name = L"circleToolStripMenuItem";
			this->circleToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->circleToolStripMenuItem->Text = L"Circle";
			this->circleToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::circleToolStripMenuItem_Click);
			// 
			// circularArcToolStripMenuItem
			// 
			this->circularArcToolStripMenuItem->Name = L"circularArcToolStripMenuItem";
			this->circularArcToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->circularArcToolStripMenuItem->Text = L"Circular Arc";
			this->circularArcToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::circularArcToolStripMenuItem_Click);
			// 
			// ellipseToolStripMenuItem
			// 
			this->ellipseToolStripMenuItem->Name = L"ellipseToolStripMenuItem";
			this->ellipseToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->ellipseToolStripMenuItem->Text = L"Ellipse";
			this->ellipseToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::ellipseToolStripMenuItem_Click);
			// 
			// parabolaToolStripMenuItem
			// 
			this->parabolaToolStripMenuItem->Name = L"parabolaToolStripMenuItem";
			this->parabolaToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->parabolaToolStripMenuItem->Text = L"Parabolic Arc";
			this->parabolaToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::parabolaToolStripMenuItem_Click);
			// 
			// hyperbolaToolStripMenuItem
			// 
			this->hyperbolaToolStripMenuItem->Name = L"hyperbolaToolStripMenuItem";
			this->hyperbolaToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->hyperbolaToolStripMenuItem->Text = L"Hyperbolic Arc";
			this->hyperbolaToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::hyperbolaToolStripMenuItem_Click);
			// 
			// cubicSplineToolStripMenuItem
			// 
			this->cubicSplineToolStripMenuItem->Name = L"cubicSplineToolStripMenuItem";
			this->cubicSplineToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->cubicSplineToolStripMenuItem->Text = L"Cubic Spline";
			this->cubicSplineToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::cubicSplineToolStripMenuItem_Click);
			// 
			// bezierCurveToolStripMenuItem
			// 
			this->bezierCurveToolStripMenuItem->Name = L"bezierCurveToolStripMenuItem";
			this->bezierCurveToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->bezierCurveToolStripMenuItem->Text = L"Bézier Curve";
			this->bezierCurveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bezierCurveToolStripMenuItem_Click);
			// 
			// bSplineToolStripMenuItem
			// 
			this->bSplineToolStripMenuItem->Name = L"bSplineToolStripMenuItem";
			this->bSplineToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->bSplineToolStripMenuItem->Text = L"B-Spline";
			this->bSplineToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bSplineToolStripMenuItem_Click);
			// 
			// generateToolStripMenuItem
			// 
			this->generateToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->meshToolStripMenuItem, 
				this->bilinearSurfaceToolStripMenuItem, this->bicubicSurfaceToolStripMenuItem, this->beziérSurfaceToolStripMenuItem, this->bSplineSurfaceToolStripMenuItem});
			this->generateToolStripMenuItem->Name = L"generateToolStripMenuItem";
			this->generateToolStripMenuItem->Size = System::Drawing::Size(66, 20);
			this->generateToolStripMenuItem->Text = L"Generate";
			// 
			// meshToolStripMenuItem
			// 
			this->meshToolStripMenuItem->Name = L"meshToolStripMenuItem";
			this->meshToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->meshToolStripMenuItem->Text = L"Quadrilateral Mesh";
			this->meshToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::meshToolStripMenuItem_Click);
			// 
			// bilinearSurfaceToolStripMenuItem
			// 
			this->bilinearSurfaceToolStripMenuItem->Name = L"bilinearSurfaceToolStripMenuItem";
			this->bilinearSurfaceToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->bilinearSurfaceToolStripMenuItem->Text = L"Bilinear Surface";
			this->bilinearSurfaceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bilinearSurfaceToolStripMenuItem_Click);
			// 
			// bicubicSurfaceToolStripMenuItem
			// 
			this->bicubicSurfaceToolStripMenuItem->Name = L"bicubicSurfaceToolStripMenuItem";
			this->bicubicSurfaceToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->bicubicSurfaceToolStripMenuItem->Text = L"Bicubic Surface";
			this->bicubicSurfaceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bicubicSurfaceToolStripMenuItem_Click);
			// 
			// beziérSurfaceToolStripMenuItem
			// 
			this->beziérSurfaceToolStripMenuItem->Name = L"beziérSurfaceToolStripMenuItem";
			this->beziérSurfaceToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->beziérSurfaceToolStripMenuItem->Text = L"Beziér Surface";
			this->beziérSurfaceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::beziérSurfaceToolStripMenuItem_Click);
			// 
			// bSplineSurfaceToolStripMenuItem
			// 
			this->bSplineSurfaceToolStripMenuItem->Name = L"bSplineSurfaceToolStripMenuItem";
			this->bSplineSurfaceToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->bSplineSurfaceToolStripMenuItem->Text = L"B-Spline Surface";
			this->bSplineSurfaceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bSplineSurfaceToolStripMenuItem_Click);
			// 
			// modifyToolStripMenuItem
			// 
			this->modifyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->shiftToolStripMenuItem, 
				this->scaleToolStripMenuItem, this->rotateToolStripMenuItem, this->deleteToolStripMenuItem});
			this->modifyToolStripMenuItem->Name = L"modifyToolStripMenuItem";
			this->modifyToolStripMenuItem->Size = System::Drawing::Size(57, 20);
			this->modifyToolStripMenuItem->Text = L"Modify";
			// 
			// shiftToolStripMenuItem
			// 
			this->shiftToolStripMenuItem->Name = L"shiftToolStripMenuItem";
			this->shiftToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->shiftToolStripMenuItem->Text = L"Shift";
			this->shiftToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::shiftToolStripMenuItem_Click);
			// 
			// scaleToolStripMenuItem
			// 
			this->scaleToolStripMenuItem->Name = L"scaleToolStripMenuItem";
			this->scaleToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->scaleToolStripMenuItem->Text = L"Scale";
			this->scaleToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::scaleToolStripMenuItem_Click);
			// 
			// rotateToolStripMenuItem
			// 
			this->rotateToolStripMenuItem->Name = L"rotateToolStripMenuItem";
			this->rotateToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->rotateToolStripMenuItem->Text = L"Rotate";
			this->rotateToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::rotateToolStripMenuItem_Click);
			// 
			// deleteToolStripMenuItem
			// 
			this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			this->deleteToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->deleteToolStripMenuItem->Text = L"Delete";
			this->deleteToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deleteToolStripMenuItem_Click);
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Location = System::Drawing::Point(14, 25);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(866, 50);
			this->panel1->TabIndex = 1;
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->button10);
			this->panel2->Controls->Add(this->textBox3);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->textBox2);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->textBox1);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Controls->Add(this->button1);
			this->panel2->Location = System::Drawing::Point(14, 25);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(866, 50);
			this->panel2->TabIndex = 2;
			this->panel2->Visible = false;
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(755, 3);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(55, 23);
			this->button10->TabIndex = 8;
			this->button10->Text = L"Top";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::button10_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(194, 25);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(30, 20);
			this->textBox3->TabIndex = 7;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Form1::textBox3_TextChanged);
			this->textBox3->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::textBox3_MouseWheel);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(164, 28);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(31, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Blue:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(116, 25);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(30, 20);
			this->textBox2->TabIndex = 5;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			this->textBox2->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::textBox2_MouseWheel);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(78, 28);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(39, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Green:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(32, 25);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(30, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			this->textBox1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::textBox1_MouseWheel);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(3, 28);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(30, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Red:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 5);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Indicate Color RGB Value";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(816, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(45, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Esc";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->toolStripStatusLabel3, 
				this->toolStripStatusLabel2, this->toolStripStatusLabel1, this->toolStripStatusLabel4});
			this->statusStrip1->Location = System::Drawing::Point(0, 646);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->statusStrip1->Size = System::Drawing::Size(894, 22);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 3;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel3
			// 
			this->toolStripStatusLabel3->AutoSize = false;
			this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
			this->toolStripStatusLabel3->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->toolStripStatusLabel3->Size = System::Drawing::Size(90, 17);
			this->toolStripStatusLabel3->Text = L"Z=0.0000e+00";
			this->toolStripStatusLabel3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->AutoSize = false;
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->toolStripStatusLabel2->Size = System::Drawing::Size(90, 17);
			this->toolStripStatusLabel2->Text = L"Y=0.0000e+00";
			this->toolStripStatusLabel2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->AutoSize = false;
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->toolStripStatusLabel1->Size = System::Drawing::Size(90, 17);
			this->toolStripStatusLabel1->Text = L"X=0.0000e+00";
			this->toolStripStatusLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// toolStripStatusLabel4
			// 
			this->toolStripStatusLabel4->AutoSize = false;
			this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
			this->toolStripStatusLabel4->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->toolStripStatusLabel4->Size = System::Drawing::Size(90, 17);
			this->toolStripStatusLabel4->Text = L"S=1.0000e+00";
			this->toolStripStatusLabel4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 15;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->textBox8);
			this->panel3->Controls->Add(this->label10);
			this->panel3->Controls->Add(this->button4);
			this->panel3->Controls->Add(this->textBox4);
			this->panel3->Controls->Add(this->label6);
			this->panel3->Controls->Add(this->textBox5);
			this->panel3->Controls->Add(this->label7);
			this->panel3->Controls->Add(this->textBox6);
			this->panel3->Controls->Add(this->label8);
			this->panel3->Controls->Add(this->label5);
			this->panel3->Controls->Add(this->button3);
			this->panel3->Controls->Add(this->button2);
			this->panel3->Location = System::Drawing::Point(14, 25);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(866, 50);
			this->panel3->TabIndex = 4;
			this->panel3->Visible = false;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(108, 25);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(100, 20);
			this->textBox8->TabIndex = 16;
			this->textBox8->Text = L"0";
			this->textBox8->TextChanged += gcnew System::EventHandler(this, &Form1::textBox8_TextChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(3, 28);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(104, 13);
			this->label10->TabIndex = 15;
			this->label10->Text = L"Construction Depth=";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(684, 3);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(55, 23);
			this->button4->TabIndex = 14;
			this->button4->Text = L"Accept";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Visible = false;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(269, 25);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 13;
			this->textBox4->Visible = false;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Form1::textBox4_TextChanged);
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox4_KeyPress);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(251, 28);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(20, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Z=";
			this->label6->Visible = false;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(145, 25);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 11;
			this->textBox5->Visible = false;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &Form1::textBox5_TextChanged);
			this->textBox5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox5_KeyPress);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(127, 28);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(20, 13);
			this->label7->TabIndex = 10;
			this->label7->Text = L"Y=";
			this->label7->Visible = false;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(21, 25);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 9;
			this->textBox6->Visible = false;
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &Form1::textBox6_TextChanged);
			this->textBox6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox6_KeyPress);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 28);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(20, 13);
			this->label8->TabIndex = 8;
			this->label8->Text = L"X=";
			this->label8->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 5);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(107, 13);
			this->label5->TabIndex = 2;
			this->label5->Text = L"Indicate start position";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(745, 3);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(55, 23);
			this->button3->TabIndex = 0;
			this->button3->Text = L"Key In";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(806, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(55, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Esc";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// panel4
			// 
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel4->Controls->Add(this->textBox7);
			this->panel4->Controls->Add(this->button5);
			this->panel4->Controls->Add(this->label9);
			this->panel4->Location = System::Drawing::Point(14, 25);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(866, 50);
			this->panel4->TabIndex = 5;
			this->panel4->Visible = false;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(5, 26);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 20);
			this->textBox7->TabIndex = 2;
			this->textBox7->TextChanged += gcnew System::EventHandler(this, &Form1::textBox7_TextChanged);
			this->textBox7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox7_KeyPress);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(806, 3);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(55, 23);
			this->button5->TabIndex = 1;
			this->button5->Text = L"Esc";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(3, 5);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(122, 13);
			this->label9->TabIndex = 0;
			this->label9->Text = L"Indicate number of sides";
			// 
			// panel5
			// 
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel5->Controls->Add(this->button11);
			this->panel5->Controls->Add(this->button9);
			this->panel5->Controls->Add(this->button8);
			this->panel5->Controls->Add(this->button7);
			this->panel5->Controls->Add(this->label11);
			this->panel5->Controls->Add(this->button6);
			this->panel5->Location = System::Drawing::Point(14, 25);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(866, 50);
			this->panel5->TabIndex = 6;
			this->panel5->Visible = false;
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(806, 3);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(55, 23);
			this->button11->TabIndex = 5;
			this->button11->Text = L"Esc";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &Form1::button11_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(246, 21);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 4;
			this->button9->Text = L"Anti-cyclic";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(165, 21);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(75, 23);
			this->button8->TabIndex = 3;
			this->button8->Text = L"Cyclic";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(84, 21);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(75, 23);
			this->button7->TabIndex = 2;
			this->button7->Text = L"Natural";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(3, 5);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(112, 13);
			this->label11->TabIndex = 1;
			this->label11->Text = L"Indicate end condition";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(3, 21);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 0;
			this->button6->Text = L"Clamped";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// panel6
			// 
			this->panel6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel6->Controls->Add(this->button12);
			this->panel6->Controls->Add(this->button15);
			this->panel6->Controls->Add(this->label12);
			this->panel6->Controls->Add(this->button16);
			this->panel6->Location = System::Drawing::Point(14, 25);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(866, 50);
			this->panel6->TabIndex = 7;
			this->panel6->Visible = false;
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(806, 3);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(55, 23);
			this->button12->TabIndex = 5;
			this->button12->Text = L"Esc";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &Form1::button12_Click);
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(94, 21);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(85, 23);
			this->button15->TabIndex = 2;
			this->button15->Text = L"Open Uniform";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &Form1::button15_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(3, 5);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(98, 13);
			this->label12->TabIndex = 1;
			this->label12->Text = L"Indicate curve type";
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(3, 21);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(85, 23);
			this->button16->TabIndex = 0;
			this->button16->Text = L"Uniform";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &Form1::button16_Click);
			// 
			// panel7
			// 
			this->panel7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel7->Controls->Add(this->button14);
			this->panel7->Controls->Add(this->button13);
			this->panel7->Controls->Add(this->label13);
			this->panel7->Location = System::Drawing::Point(14, 25);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(866, 50);
			this->panel7->TabIndex = 8;
			this->panel7->Visible = false;
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(745, 3);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(55, 23);
			this->button14->TabIndex = 6;
			this->button14->Text = L"Accept";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &Form1::button14_Click);
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(806, 3);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(55, 23);
			this->button13->TabIndex = 5;
			this->button13->Text = L"Esc";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &Form1::button13_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(3, 5);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(41, 13);
			this->label13->TabIndex = 1;
			this->label13->Text = L"label13";
			// 
			// panel8
			// 
			this->panel8->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel8->Controls->Add(this->label17);
			this->panel8->Controls->Add(this->label16);
			this->panel8->Controls->Add(this->label15);
			this->panel8->Controls->Add(this->textBox11);
			this->panel8->Controls->Add(this->textBox10);
			this->panel8->Controls->Add(this->textBox9);
			this->panel8->Controls->Add(this->button18);
			this->panel8->Controls->Add(this->label14);
			this->panel8->Location = System::Drawing::Point(14, 25);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(866, 50);
			this->panel8->TabIndex = 9;
			this->panel8->Visible = false;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(272, 28);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(26, 13);
			this->label17->TabIndex = 11;
			this->label17->Text = L"dZ=";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(138, 28);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(26, 13);
			this->label16->TabIndex = 10;
			this->label16->Text = L"dY=";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(3, 28);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(26, 13);
			this->label15->TabIndex = 9;
			this->label15->Text = L"dX=";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(299, 25);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(100, 20);
			this->textBox11->TabIndex = 8;
			this->textBox11->TextChanged += gcnew System::EventHandler(this, &Form1::textBox11_TextChanged);
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(165, 25);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(100, 20);
			this->textBox10->TabIndex = 7;
			this->textBox10->TextChanged += gcnew System::EventHandler(this, &Form1::textBox10_TextChanged);
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(30, 25);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(100, 20);
			this->textBox9->TabIndex = 6;
			this->textBox9->TextChanged += gcnew System::EventHandler(this, &Form1::textBox9_TextChanged);
			// 
			// button18
			// 
			this->button18->Location = System::Drawing::Point(806, 3);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(55, 23);
			this->button18->TabIndex = 5;
			this->button18->Text = L"Esc";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &Form1::button18_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(3, 5);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(100, 13);
			this->label14->TabIndex = 1;
			this->label14->Text = L"Indicate shift vector";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(894, 668);
			this->Controls->Add(this->panel8);
			this->Controls->Add(this->panel7);
			this->Controls->Add(this->panel6);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel5);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"CGG Applet";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseWheel);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			this->panel7->ResumeLayout(false);
			this->panel7->PerformLayout();
			this->panel8->ResumeLayout(false);
			this->panel8->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

	#pragma endregion


	/******************************************************************
	******************User-Defined Functions - Start*******************
    *******************************************************************/

	private:
		 void Paint(PaintEventArgs^ pe){
			   if(paint_lock){
				    OnPaint(pe);
					paint_lock = false;
					resample = false;
			   }
		 }

		 void AddPoint(System::Boolean ctrl){
			 if(ctrl) point_argument = vector3D(Convert::ToDouble(textBox6->Text), Convert::ToDouble(textBox5->Text), Convert::ToDouble(textBox4->Text));
			 else point_argument = vector3D(XFormto3D(GetCurPos()));
			 if(object_creation_state){
				 switch(object_list_header->GetNext()->GetObjTypeId()){
				 case 1:
					 ((Object_PolyLine^)(object_list_header->GetNext()))->AddVertex(point_argument);
					 break;
				 case 6:
					 if(object_creation_state == 21){
						 if(ctrl) ((Object_Cubic_Spline^)(object_list_header->GetNext()))->start_derivative = point_argument;
						 else((Object_Cubic_Spline^)(object_list_header->GetNext()))->start_derivative = point_argument - *((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertices[0];
					 }
					 else if(object_creation_state == 24){
						 if(ctrl) ((Object_Cubic_Spline^)(object_list_header->GetNext()))->end_derivative = point_argument;
						 else((Object_Cubic_Spline^)(object_list_header->GetNext()))->end_derivative = point_argument - *((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertices[((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position - 1];
					 }
					 else ((Object_Cubic_Spline^)(object_list_header->GetNext()))->AddVertex(point_argument);
					 break;
				 case 7:
					 ((Object_Bezier_Curve^)(object_list_header->GetNext()))->AddVertex(point_argument);
					 break;
				 case 8:
					 ((Object_BSpline^)(object_list_header->GetNext()))->BSplineAddVertex(point_argument);
					 break;
				 case 9:
					 ((Object_Mesh^)(object_list_header->GetNext()))->AddVertex(point_argument);
					 break;
				 case 11:
					 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->AddVertex(point_argument);
					 break;
				 case 12:
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->BSplineAddVertex(point_argument);
					 break;
				 }
			 }
			 switch(object_creation_state){
			 case 1:
			 case 3:
			 case 4:
			 case 16:
			 case 17:
			 case 21:
			 case 22:
			 case 30:
			 case 34:
			 case 35:
			 case 38:
			 case 39:
			 case 41:
			 case 43:
			 case 44:
			 case 45:
			 case 47:
			 case 48:
			 case 50:
			 case 53:
			 case 54:
			 case 56:
			 case 60:
			 case 61:
			 case 62:
			 case 63:
			 case 64:
			 case 65:
			 case 66:
			 case 67:
			 case 68:
			 case 69:
			 case 70:
			 case 71:
			 case 72:
			 case 73:
			 case 74:
				 object_creation_state++;
				 break;
			 case 42:
				 if(((Object_Mesh^)(object_list_header->GetNext()))->current_position_0 == 1) object_creation_state--;
				 break;
			 case 51:
				 if(((Object_Bezier_Surf^)(object_list_header->GetNext()))->current_position_0 == 1) object_creation_state--;
				 break;
			 case 57:
				 if(((Object_BSpline_Surf^)(object_list_header->GetNext()))->current_position_0 == 1) object_creation_state--;
				 break;
			 case 46:
			 case 75:
				 object_list_header->GetNext()->FinalizeObject();
				 PanelEscape();
				 break;
			 case 25:
			 case 76:
				 temp_vector_0 = point_argument;
				 object_creation_state++;
				 break;
			 case 26:
			 case 31:
				 if(!(point_argument == temp_vector_0)){
					temp_vector_1 = point_argument;
					object_creation_state++;
				 }
				 break;
			 case 77:
				 if(!(point_argument == temp_vector_0)){
					temp_vector_1 = point_argument - temp_vector_0;
					temp_vector_1.Unit();
					object_creation_state++;
				 }
				 break;
			 case 20:
				 if(((Object_Cubic_Spline^)(object_list_header->GetNext()))->end_condition_mode) object_creation_state++;
				 object_creation_state++;
				 break;
			 case 32:
				 if((!(point_argument == temp_vector_0)) && (!(point_argument == temp_vector_1))){
					object_list_header->GetNext()->FinalizeObject();
 					PanelEscape();
				 }
				 break;
			 case 27:{
				 vector3D directrix = temp_vector_1 - temp_vector_0;
				 vector3D focus = point_argument - temp_vector_0;
				 directrix.Unit();
				 ((Object_Parabola^)(object_list_header->GetNext()))->parabola_x_axis = directrix;
				 focus -= directrix * directrix.DotProduct(focus);
				 ((Object_Parabola^)(object_list_header->GetNext()))->parabola_xy_ratio = 2 * focus.Magnitude();
				 ((Object_Parabola^)(object_list_header->GetNext()))->parabola_origin = point_argument - focus * 0.5;
				 focus.Unit();
				 ((Object_Parabola^)(object_list_header->GetNext()))->parabola_y_axis = focus;
				 object_creation_state++;
				 }
				 break;
			 case 78:
				 if(!(point_argument == temp_vector_0)){
					 point_argument -= temp_vector_0;
					 point_argument.Unit();
					 if(!(point_argument == temp_vector_1)){
						 ((Object_Hyperbola^)(object_list_header->GetNext()))->hyperbola_origin = temp_vector_0;
						 temp_vector_0 = point_argument + temp_vector_1;
						 temp_vector_0.Unit();
						 ((Object_Hyperbola^)(object_list_header->GetNext()))->hyperbola_x_axis = temp_vector_0;
						 temp_vector_0 = point_argument - temp_vector_1;
						 temp_vector_0.Unit();
						 ((Object_Hyperbola^)(object_list_header->GetNext()))->hyperbola_y_axis = temp_vector_0;
						 ((Object_Hyperbola^)(object_list_header->GetNext()))->hyperbola_xy_ratio = Math::Abs(point_argument.DotProduct(((Object_Hyperbola^)(object_list_header->GetNext()))->hyperbola_x_axis) / point_argument.DotProduct(temp_vector_0));
						 object_creation_state++;
					 }
				 }
				 break;
			 case 2:
			 case 9:
			 case 11:
			 case 15:
			 case 24: // end point derivative of cubic spline
			 case 255: // final operations for object creation are performed here
				 switch(object_list_header->GetNext()->GetObjTypeId()){
				 case 1:
					 ((Object_PolyLine^)(object_list_header->GetNext()))->current_position -= 3;
					 ((Object_PolyLine^)(object_list_header->GetNext()))->ClearExtraSpace();
					 break;
				 case 2:
					 ((Object_Polygon^)(object_list_header->GetNext()))->PolygonGenerate(view_x, view_y);
					 break;
				 case 3:
					 ((Object_Ellipse^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 6:
					 if(object_creation_state == 24) ((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position--;
					 else ((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position -= 3;
					 ((Object_Cubic_Spline^)(object_list_header->GetNext()))->ClearExtraSpace();
					 ((Object_Cubic_Spline^)(object_list_header->GetNext()))->CalculateCoefficients();
					 ((Object_Cubic_Spline^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 7:
					 ((Object_Bezier_Curve^)(object_list_header->GetNext()))->current_position -= 3;
					 ((Object_Bezier_Curve^)(object_list_header->GetNext()))->ClearExtraSpace();
					 ((Object_Bezier_Curve^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 9:
					 ((Object_Mesh^)(object_list_header->GetNext()))->ClearExtraSpace();
					 break;
				 case 11:
					 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->ClearExtraSpace();
					 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 }
				 object_list_header->GetNext()->FinalizeObject();
				 PanelEscape();
				 break;
			 }
			 switch(object_modification_state){
			 case 7:
			 case 10:
				 temp_vector_0 = point_argument;
				 object_modification_state++;
				 break;
			 case 11:
				 if(!(point_argument == temp_vector_0)){
					 temp_vector_1 = point_argument;
					 object_modification_state++;
				 }
				 break;
			 }
			 Paint(pe);
		 }

		 void PreviewPoint(System::Boolean ctrl){
			 if(preview_lock){
				 if(ctrl) point_argument = vector3D(Convert::ToDouble(textBox6->Text), Convert::ToDouble(textBox5->Text), Convert::ToDouble(textBox4->Text));
				 else point_argument = vector3D(XFormto3D(GetCurPos()));
				 switch(object_list_header->GetNext()->GetObjTypeId()){
				 case 0:
					 if(object_creation_state == 1) ((Object_Line^)(object_list_header->GetNext()))->line_start = point_argument;
					 ((Object_Line^)(object_list_header->GetNext()))->line_end = point_argument;
					 break;
				 case 1:
					 *((Object_PolyLine^)(object_list_header->GetNext()))->vertices[(((Object_PolyLine^)(object_list_header->GetNext()))->current_position) - 1] = point_argument;
					 break;
				 case 2:
					 ((Object_Polygon^)(object_list_header->GetNext()))->polygon_center = point_argument;
					 ((Object_Polygon^)(object_list_header->GetNext()))->PolygonGenerate(view_x, view_y);
					 break;
				 case 3:
					 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_axis = view_x * Math::Cos(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation) + view_y * Math::Sin(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation);
					 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_y_axis = view_x * (-Math::Sin(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation)) + view_y * (-Math::Cos(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation));
					 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_center = point_argument;
					 ((Object_Ellipse^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 4:
					 ((Object_Parabola^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 5:
					 ((Object_Hyperbola^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 6:
					 if(object_creation_state == 20) *((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertices[(((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position) - 1] = point_argument;
					 else if(object_creation_state == 21){
						 if(ctrl) ((Object_Cubic_Spline^)(object_list_header->GetNext()))->start_derivative = point_argument;
						 else((Object_Cubic_Spline^)(object_list_header->GetNext()))->start_derivative = point_argument - *((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertices[0];
					 }
					 else{
						if(object_creation_state == 24){
							if(ctrl) ((Object_Cubic_Spline^)(object_list_header->GetNext()))->end_derivative = point_argument;
							else((Object_Cubic_Spline^)(object_list_header->GetNext()))->end_derivative = point_argument - *((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertices[((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position - 1];
						}
						else *((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertices[(((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position) - 1] = point_argument;
						((Object_Cubic_Spline^)(object_list_header->GetNext()))->CalculateCoefficients();
						((Object_Cubic_Spline^)(object_list_header->GetNext()))->Sample(global_scale);
					 }
					 break;
				 case 7:
					 *((Object_Bezier_Curve^)(object_list_header->GetNext()))->vertices[(((Object_Bezier_Curve^)(object_list_header->GetNext()))->current_position) - 1] = point_argument;
					 ((Object_Bezier_Curve^)(object_list_header->GetNext()))->PolygonLengthUpdate();
					 ((Object_Bezier_Curve^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 8:
					 *((Object_BSpline^)(object_list_header->GetNext()))->vertices[(((Object_BSpline^)(object_list_header->GetNext()))->current_position) - 1] = point_argument;
					 ((Object_BSpline^)(object_list_header->GetNext()))->PolygonLengthUpdate();
					 ((Object_BSpline^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 9:
					 *((Object_Mesh^)(object_list_header->GetNext()))->vertices[((((Object_Mesh^)(object_list_header->GetNext()))->current_position_0) - 1), ((Object_Mesh^)(object_list_header->GetNext()))->current_position_1] = point_argument;
					 break;
				 case 11:
					 *((Object_Bezier_Surf^)(object_list_header->GetNext()))->vertices[((((Object_Bezier_Surf^)(object_list_header->GetNext()))->current_position_0) - 1), ((Object_Bezier_Surf^)(object_list_header->GetNext()))->current_position_1] = point_argument;
					 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->PolygonLengthUpdate();
					 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 12:
					 *((Object_BSpline_Surf^)(object_list_header->GetNext()))->vertices[((((Object_BSpline_Surf^)(object_list_header->GetNext()))->current_position_0) - 1), ((Object_BSpline_Surf^)(object_list_header->GetNext()))->current_position_1] = point_argument;
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->PolygonLengthUpdate();
					 if(object_creation_state > 55) ((Object_BSpline_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 }
				 switch(object_creation_state){
				 case 43:
				 case 44:
				 case 45:
					 *((Object_Bilinear_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 43] = point_argument;
					 break;
				 case 46:
					 *((Object_Bilinear_Surf^)(object_list_header->GetNext()))->vertices[3] = point_argument;
					 ((Object_Bilinear_Surf^)(object_list_header->GetNext()))->PolygonLengthUpdate();
					 ((Object_Bilinear_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 60:
				 case 61:
				 case 62:
					 *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 60] = point_argument;
					 break;
				 case 63:
					 *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[3] = point_argument;
					 ((Object_Bicubic_Surf^)(object_list_header->GetNext()))->PolygonLengthUpdate();
					 ((Object_Bicubic_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 64:
				 case 65:
				 case 66:
				 case 67:
					 if(ctrl) *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 60] = point_argument;
					 else *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 60] = point_argument - *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 64];
					 ((Object_Bicubic_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 68:
				 case 69:
				 case 70:
				 case 71:
					 if(ctrl) *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 60] = point_argument;
					 else *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 60] = point_argument - *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 68];
					 ((Object_Bicubic_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 case 72:
				 case 73:
				 case 74:
				 case 75:
					 if(ctrl) *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 60] = point_argument;
					 else *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 60] = point_argument - *((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[object_creation_state - 72];
					 ((Object_Bicubic_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 break;
				 }
				 Paint(pe);
			 }
		 }

		 void PanelEnter(void){
			 click_permit = false;
			 object_creation_state = 0;
			 object_modification_state = 0;
			 selected_object->selected = false;
			 if(object_list_header->GetNext())
				 if(!(object_list_header->GetNext()->IsFinalized()))
					 delete object_list_header->DeleteObject();
			 this->Focus();
			 Paint(pe);
		 }

		 void PanelEscape(void){
			object_creation_state = 0;
			object_modification_state = 0;
			selected_object->selected = false;
			if(object_list_header->GetNext())
				if(!(object_list_header->GetNext()->IsFinalized()))
					delete object_list_header->DeleteObject();
			panelarray[activepanel]->Visible = false;
			panelarray[0]->Visible = true;
			activepanel = 0;
			this->Focus();
			Paint(pe);
		 }

		 void InitializeColors(void){
			//Graphics Variables - Start
			pen_color = 0xFF00FF00;
			brush_color_0 = 0xFF000000;
			brush_color_1 = 0xFF323250;
			brush_colors = gcnew array<Color> {Color::FromArgb(brush_color_0), Color::FromArgb(brush_color_1)};
			pen_0 = gcnew Pen(Color::FromArgb(pen_color));
			pen_0->LineJoin = System::Drawing::Drawing2D::LineJoin::Miter;
			pen_0->MiterLimit = 100.0;
			pen_1 = gcnew Pen(Color::FromArgb(EDGECOLOR));
			pen_1->LineJoin = System::Drawing::Drawing2D::LineJoin::Miter;
			pen_1->MiterLimit = 100.0;
			pen_1->Width = 2.0;
			pen_2 = gcnew Pen(Color::FromArgb(0xFFFF0000));
			pen_2->Width = 4.0;
			pen_2->EndCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;
			pen_3 = gcnew Pen(Color::FromArgb(0xFF00FF00));
			pen_3->Width = 4.0;
			pen_3->EndCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;
			pen_4 = gcnew Pen(Color::FromArgb(0xFF0000FF));
			pen_4->Width = 4.0;
			pen_4->EndCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;
			pen_5 = gcnew Pen(Color::FromArgb(pen_color));
			pen_5->LineJoin = System::Drawing::Drawing2D::LineJoin::Miter;
			pen_5->MiterLimit = 100.0;
			pen_5->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot;
			pen_6 = gcnew Pen(Color::FromArgb(pen_color));
			pen_6->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot;
			pen_6->EndCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;
			brush_0 = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Point(0, PANE_TOP), System::Drawing::Point(0, PANE_BOTTOM), Color::FromArgb(brush_color_0), Color::FromArgb(brush_color_1));
		 }

		 void InitializeAll(void){
			paint_lock = true;
			preview_lock = true;
			Graphics^ graphics = this->CreateGraphics();
			System::Drawing::Rectangle DrawingPaneRect = System::Drawing::Rectangle(PANE_LEFT, PANE_TOP, PANE_WIDTH, PANE_HEIGHT);
			pe = gcnew PaintEventArgs(graphics, DrawingPaneRect);
			form_cli_difference = this->Size - this->ClientSize;
			resample = false;

			// Input Variables Initialization - Start
			click_control = false;
			drag_control = false;
			click_key_switch = true;
			// Input Variables Initialization - End

			//Static Components - Start
			pe->Graphics->FillRectangle(brush_0, PANE_LEFT, PANE_TOP, PANE_WIDTH, PANE_HEIGHT);
			pe->Graphics->DrawRectangle(pen_1, PANE_LEFT, PANE_TOP, PANE_WIDTH, PANE_HEIGHT);
			//Static Components - End

			//Panels - Start
			panelarray = gcnew array<System::Windows::Forms::Panel^>{panel1, panel2, panel3, panel4, panel5, panel6, panel7, panel8};
			panel_specifier = gcnew array<System::Byte>(SPECIFIEDPANELS);
			panel_controller = gcnew array<System::Byte>{1};
			activepanel = 0;
			//Panels - End	

			// System Variables Initialization - Start
			axes_origin = System::Drawing::Point(AXES_LEFT, AXES_TOP);
			object_list_header = gcnew Screen_Object(0, 0);
			selected_object = object_list_header;
			global_scale = 1;
			global_shift_x = PANE_HMID;
			global_shift_y = PANE_VMID;
			view_x = vector3D(1, 0, 0);
			view_y = vector3D(0, 1, 0);
			view_z = vector3D(0, 0, 1);
			construction_depth = 0;
			object_creation_state = 0;
			object_modification_state = 0;
			// System Variables Initialization - End

			Paint(pe);
		 }

		 void ClearColors(void){
			delete pen_0;
			delete pen_1;
			delete pen_2;
			delete pen_3;
			delete pen_4;
			delete pen_5;
			delete pen_6;
			delete brush_0;
		 }

		 void ClearAll(void){
			delete pe;
			delete panel_specifier;
			delete panel_controller;
			delete panelarray;

			// System Variables - Start
			delete object_list_header;
			// System Variables - End
		 }

		 void StatusUpdate(void){
			 toolStripStatusLabel1->Text = "X=" + (XFormto3D(GetCurPos()).p[0]).ToString("#.0000e+00");
			 toolStripStatusLabel2->Text = "Y=" + (XFormto3D(GetCurPos()).p[1]).ToString("#.0000e+00");
			 toolStripStatusLabel3->Text = "Z=" + (XFormto3D(GetCurPos()).p[2]).ToString("#.0000e+00");
		 }

		 System::Boolean IsCursorInPane(void){
			System::UInt16 temp1;
			if((temp1 = (this->MousePosition.X - (this->Location.X + form_cli_difference.Width + PANE_LEFTM2))) >= 0)
				if(temp1 <= PANE_WIDTHM3)
					if((temp1 = (this->MousePosition.Y - (this->Location.Y + form_cli_difference.Height + PANE_TOPM2))) >= 0)
						if(temp1 <= PANE_HEIGHTM3) return true; 
			return false;
		 }

		 System::Boolean IsPointInPane(System::Drawing::Point% pnt){
			System::Int32 temp0;
			if((temp0 = (pnt.X - PANE_LEFT1)) >= 0)
				if(temp0 <= PANE_WIDTHM3)
					if((temp0 = (pnt.Y - PANE_TOP1)) >= 0)
						if(temp0 <= PANE_HEIGHTM3) return true; 
			return false;
		 }

		 System::Boolean PointCompatibility(System::Drawing::Point% pnt0, System::Drawing::Point% pnt1){
			System::Int32 temp0 = temp0 = (pnt0.X - PANE_LEFT1);
			System::Int32 temp1 = (pnt1.X - PANE_LEFT1);
			if(!((temp0 < 0) && (temp1 < 0)))
				if(!((temp0 > PANE_WIDTHM2) && (temp1 > PANE_WIDTHM2))){
					temp0 = (pnt0.Y - PANE_TOP1);
					temp1 = (pnt1.Y - PANE_TOP1);
					if(!((temp0 < 0) && (temp1 < 0)))
						if(!((temp0 > PANE_HEIGHTM2) && (temp1 > PANE_HEIGHTM2))) return true;
				}
			return false;
		 }
		 
		 vector3D XFormto3D(System::Drawing::Point% pnt){
			 return (((view_x * ((System::Double)pnt.X - global_shift_x)) + (-view_y * ((System::Double)pnt.Y - global_shift_y))) / (System::Double)(global_scale) + view_z * (System::Double)(construction_depth));
		 }

		 System::Drawing::Point XFormto2D(vector3D% pnt){
			 return System::Drawing::Point((System::Int32)(Math::Round(((pnt.DotProduct(view_x)) * global_scale) + global_shift_x + PANE_LEFT1)),
										   (System::Int32)(Math::Round((((pnt.DotProduct(-view_y)) * global_scale) + global_shift_y + PANE_TOP1))));
		 }

		 System::Drawing::Size XFormAxesto2D(vector3D% pnt){
			 return System::Drawing::Size((System::Int32)(Math::Round(((pnt.DotProduct(view_x)) * AXES_LENGTH))),
										   (System::Int32)(Math::Round((((pnt.DotProduct(-view_y)) * AXES_LENGTH)))));
		 }

		 System::Drawing::Point GetCurPos(void){
			 return System::Drawing::Point(this->MousePosition.X - (this->Location.X + form_cli_difference.Width + PANE_LEFTM2),
										   this->MousePosition.Y - (this->Location.Y + form_cli_difference.Height + PANE_TOPM2));
		 }

		 System::Double Magnitude2D(System::Drawing::Point pnt){
			 return Math::Sqrt(Math::Pow(pnt.X, 2.0) + Math::Pow(pnt.Y, 2.0));
		 }

		 void DrawObject(Screen_Object^ s_object){
			 System::Boolean modification_flag = (object_modification_state && (object_modification_state != 3));
			 pen_0->Color = Color::FromArgb(s_object->object_color);
			 if(s_object->selected && modification_flag) pen_0->Color = Color::FromArgb(0xFFFFFFFF);
			 switch(s_object->GetObjTypeId()){
			 case 0:
				 DrawClippedLine(pen_0, XFormto2D(((Object_Line^)s_object)->line_start), XFormto2D(((Object_Line^)s_object)->line_end));
				 if(s_object->selected){
					 DrawPoint(XFormto2D(((Object_Line^)s_object)->line_start));
					 DrawPoint(XFormto2D(((Object_Line^)s_object)->line_end));
				 }
				 break;
			 case 1:
				 for(((Object_PolyLine^)s_object)->current_position = 1; ((Object_PolyLine^)s_object)->current_position < ((Object_PolyLine^)s_object)->vertex_array_length; ((Object_PolyLine^)s_object)->current_position++)
					 DrawClippedLine(pen_0, XFormto2D(*(((Object_PolyLine^)s_object)->vertices[((Object_PolyLine^)s_object)->current_position])), XFormto2D(*(((Object_PolyLine^)s_object)->vertices[(((Object_PolyLine^)s_object)->current_position) - 1])));
				 if(s_object->selected)
					 for(((Object_PolyLine^)s_object)->current_position = 0; ((Object_PolyLine^)s_object)->current_position < ((Object_PolyLine^)s_object)->vertex_array_length; ((Object_PolyLine^)s_object)->current_position++)
						 DrawPoint(XFormto2D(*(((Object_PolyLine^)s_object)->vertices[((Object_PolyLine^)s_object)->current_position])));
				 break;
			 case 2:
				 for(((Object_Polygon^)s_object)->current_position = 1; ((Object_Polygon^)s_object)->current_position < ((Object_Polygon^)s_object)->vertex_array_length; ((Object_Polygon^)s_object)->current_position++)
					 DrawClippedLine(pen_0, XFormto2D(*(((Object_Polygon^)s_object)->vertices[((Object_Polygon^)s_object)->current_position])), XFormto2D(*(((Object_Polygon^)s_object)->vertices[(((Object_Polygon^)s_object)->current_position) - 1])));
				 if(((Object_Polygon^)s_object)->vertex_array_length) DrawClippedLine(pen_0, XFormto2D(*(((Object_Polygon^)s_object)->vertices[0])), XFormto2D(*(((Object_Polygon^)s_object)->vertices[(((Object_Polygon^)s_object)->current_position) - 1])));
				 break;
			 case 3:
				 switch(object_creation_state){
				 case 30:
					 temp_vector_0 = point_argument;
					 DrawPoint(XFormto2D(temp_vector_0));
					 break; 					 
				 case 31:
					 if(!(point_argument == temp_vector_0)){
						temp_vector_1 = point_argument;
						DrawPoint(XFormto2D(temp_vector_1));
					 }
					 DrawPoint(XFormto2D(temp_vector_0));					 
					 break;
				 case 32:{
					 if((!(point_argument == temp_vector_0)) && (!(point_argument == temp_vector_1))){
						DrawPoint(XFormto2D(point_argument));
						System::Double x1, x2, xm, y2, ym;
						vector3D temp_axis_0 = temp_vector_0 - temp_vector_1;
						vector3D temp_axis_1 = point_argument - temp_vector_1;
						//Gram-Schmidt Algorithm - Start
						x1 = temp_axis_0.Magnitude();
						temp_axis_0.Unit();
						x2 = temp_axis_1.DotProduct(temp_axis_0);
						temp_axis_1 -= temp_axis_0 * x2;
						y2 = temp_axis_1.Magnitude();
						temp_axis_1.Unit();
						//Gram-Schmidt Algorithm - End
						ym = (Math::Pow(y2, 2) + Math::Pow(x2, 2) - x1 * x2) / (2 * y2);
						xm = x1 / 2;
						((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_size = ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_y_size = Math::Sqrt(Math::Pow(xm, 2) + Math::Pow(ym, 2));
						((Object_Ellipse^)(object_list_header->GetNext()))->ArcLengthUpdate();
						((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_center = temp_vector_1 + temp_axis_0 * xm + temp_axis_1 * ym;
						vector3D temp_axis_2 = temp_axis_0.XProduct(temp_axis_1);
						x1 = -Math::Atan2(ym, xm);
						temp_axis_0.Rotate(temp_axis_2, x1);
						temp_axis_1.Rotate(temp_axis_2, x1);
						((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_axis = temp_axis_0;
						((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_y_axis = temp_axis_1;
						((Object_Ellipse^)(object_list_header->GetNext()))->angle_difference = Math::Atan2((xm - x2), (y2 - ym)) - PI1H - x1;
						((Object_Ellipse^)(object_list_header->GetNext()))->Sample(global_scale);
					 }
					 DrawPoint(XFormto2D(temp_vector_0));
					 DrawPoint(XFormto2D(temp_vector_1));
				 }
				 }
				 if(resample) ((Object_Ellipse^)(s_object))->Sample(global_scale);
				 for(((Object_Ellipse^)s_object)->s_current_position = 1; ((Object_Ellipse^)s_object)->s_current_position < ((Object_Ellipse^)s_object)->s_vertex_array_length; ((Object_Ellipse^)s_object)->s_current_position++)
					 DrawClippedLine(pen_0, XFormto2D(*(((Object_Ellipse^)s_object)->sampled_vertices[((Object_Ellipse^)s_object)->s_current_position])), XFormto2D(*(((Object_Ellipse^)s_object)->sampled_vertices[(((Object_Ellipse^)s_object)->s_current_position) - 1])));
				 break;
			 case 4:
				 if(resample) ((Object_Parabola^)(s_object))->Sample(global_scale);
				 if(s_object->selected && object_creation_state){
					 DrawPoint(XFormto2D(*((Object_Parabola^)(object_list_header->GetNext()))->sampled_vertices[0]));
					 DrawPoint(XFormto2D(*((Object_Parabola^)(object_list_header->GetNext()))->sampled_vertices[((Object_Parabola^)s_object)->s_vertex_array_length - 1]));
				 }				 
				 for(((Object_Parabola^)s_object)->s_current_position = 1; ((Object_Parabola^)s_object)->s_current_position < ((Object_Parabola^)s_object)->s_vertex_array_length; ((Object_Parabola^)s_object)->s_current_position++)
					 DrawClippedLine(pen_0, XFormto2D(*(((Object_Parabola^)s_object)->sampled_vertices[((Object_Parabola^)s_object)->s_current_position])), XFormto2D(*(((Object_Parabola^)s_object)->sampled_vertices[(((Object_Parabola^)s_object)->s_current_position) - 1])));
				 break;
			 case 5:
				 if(resample) ((Object_Hyperbola^)(s_object))->Sample(global_scale);
				 if(s_object->selected && object_creation_state > 79){
					 DrawPoint(XFormto2D(*((Object_Hyperbola^)(object_list_header->GetNext()))->sampled_vertices[0]));
					 DrawPoint(XFormto2D(*((Object_Hyperbola^)(object_list_header->GetNext()))->sampled_vertices[((Object_Hyperbola^)s_object)->s_vertex_array_length - 1]));
				 }
				 for(((Object_Hyperbola^)s_object)->s_current_position = 1; ((Object_Hyperbola^)s_object)->s_current_position < ((Object_Hyperbola^)s_object)->s_vertex_array_length; ((Object_Hyperbola^)s_object)->s_current_position++)
					 DrawClippedLine(pen_0, XFormto2D(*(((Object_Hyperbola^)s_object)->sampled_vertices[((Object_Hyperbola^)s_object)->s_current_position])), XFormto2D(*(((Object_Hyperbola^)s_object)->sampled_vertices[(((Object_Hyperbola^)s_object)->s_current_position) - 1])));
				 break;
			 case 6:
				 if(resample && !(s_object->selected && (object_creation_state == 21))) ((Object_Cubic_Spline^)(s_object))->Sample(global_scale);
				 if(s_object->selected){
					pen_6->Color = Color::FromArgb(s_object->object_color);
					if(modification_flag) pen_6->Color = Color::FromArgb(0xFFFFFFFF);
					for(((Object_Cubic_Spline^)s_object)->current_position = 0; ((Object_Cubic_Spline^)s_object)->current_position < ((Object_Cubic_Spline^)s_object)->vertex_array_length; ((Object_Cubic_Spline^)s_object)->current_position++)
						DrawPoint(XFormto2D(*(((Object_Cubic_Spline^)s_object)->vertices[((Object_Cubic_Spline^)s_object)->current_position])));
					DrawClippedLine(pen_6, XFormto2D(*(((Object_Cubic_Spline^)s_object)->vertices[0])), XFormto2D(((Object_Cubic_Spline^)s_object)->start_derivative + *(((Object_Cubic_Spline^)s_object)->vertices[0])));
					DrawClippedLine(pen_6, XFormto2D(*(((Object_Cubic_Spline^)s_object)->vertices[((Object_Cubic_Spline^)s_object)->vertex_array_length - 1])), XFormto2D(((Object_Cubic_Spline^)s_object)->end_derivative + *(((Object_Cubic_Spline^)s_object)->vertices[((Object_Cubic_Spline^)s_object)->vertex_array_length - 1])));
				 }
				 for(((Object_Cubic_Spline^)s_object)->s_current_position = 1; ((Object_Cubic_Spline^)s_object)->s_current_position < ((Object_Cubic_Spline^)s_object)->s_vertex_array_length; ((Object_Cubic_Spline^)s_object)->s_current_position++)
					 DrawClippedLine(pen_0, XFormto2D(*(((Object_Cubic_Spline^)s_object)->sampled_vertices[((Object_Cubic_Spline^)s_object)->s_current_position])), XFormto2D(*(((Object_Cubic_Spline^)s_object)->sampled_vertices[(((Object_Cubic_Spline^)s_object)->s_current_position) - 1])));
				 break;
			 case 7:
				 if(resample) ((Object_Bezier_Curve^)(s_object))->Sample(global_scale);
				 if(s_object->selected){
					 pen_5->Color = Color::FromArgb(s_object->object_color);
					 if(modification_flag) pen_5->Color = Color::FromArgb(0xFFFFFFFF);
					 for(((Object_Bezier_Curve^)s_object)->current_position = 1; ((Object_Bezier_Curve^)s_object)->current_position < ((Object_Bezier_Curve^)s_object)->vertex_array_length; ((Object_Bezier_Curve^)s_object)->current_position++){
						 DrawClippedLine(pen_5, XFormto2D(*(((Object_Bezier_Curve^)s_object)->vertices[((Object_Bezier_Curve^)s_object)->current_position])), XFormto2D(*(((Object_Bezier_Curve^)s_object)->vertices[(((Object_Bezier_Curve^)s_object)->current_position) - 1])));
						 DrawPoint(XFormto2D(*(((Object_Bezier_Curve^)s_object)->vertices[((Object_Bezier_Curve^)s_object)->current_position])));
					 }
					 DrawPoint(XFormto2D(*(((Object_Bezier_Curve^)s_object)->vertices[0])));
				 }
				 for(((Object_Bezier_Curve^)s_object)->s_current_position = 1; ((Object_Bezier_Curve^)s_object)->s_current_position < ((Object_Bezier_Curve^)s_object)->s_vertex_array_length; ((Object_Bezier_Curve^)s_object)->s_current_position++)
					 DrawClippedLine(pen_0, XFormto2D(*(((Object_Bezier_Curve^)s_object)->sampled_vertices[((Object_Bezier_Curve^)s_object)->s_current_position])), XFormto2D(*(((Object_Bezier_Curve^)s_object)->sampled_vertices[(((Object_Bezier_Curve^)s_object)->s_current_position) - 1])));
				 break;
			 case 8:
				 if(resample) ((Object_BSpline^)(s_object))->Sample(global_scale);
				 if(s_object->selected){
					 pen_5->Color = Color::FromArgb(s_object->object_color);
					 if(modification_flag) pen_5->Color = Color::FromArgb(0xFFFFFFFF);
					 for(((Object_BSpline^)s_object)->current_position = 1; ((Object_BSpline^)s_object)->current_position < ((Object_BSpline^)s_object)->vertex_array_length; ((Object_BSpline^)s_object)->current_position++){
						 DrawClippedLine(pen_5, XFormto2D(*(((Object_BSpline^)s_object)->vertices[((Object_BSpline^)s_object)->current_position])), XFormto2D(*(((Object_BSpline^)s_object)->vertices[(((Object_BSpline^)s_object)->current_position) - 1])));
						 DrawPoint(XFormto2D(*(((Object_BSpline^)s_object)->vertices[((Object_BSpline^)s_object)->current_position])));
					 }
					 DrawPoint(XFormto2D(*(((Object_BSpline^)s_object)->vertices[0])));
				 }
				 for(((Object_BSpline^)s_object)->s_current_position = 1; ((Object_BSpline^)s_object)->s_current_position < ((Object_BSpline^)s_object)->s_vertex_array_length; ((Object_BSpline^)s_object)->s_current_position++)
					 DrawClippedLine(pen_0, XFormto2D(*(((Object_BSpline^)s_object)->sampled_vertices[((Object_BSpline^)s_object)->s_current_position])), XFormto2D(*(((Object_BSpline^)s_object)->sampled_vertices[(((Object_BSpline^)s_object)->s_current_position) - 1])));
				 break;
			 case 9:
				 {
					 System::UInt32 cnt0, cnt1;
					 for(cnt0 = 1; cnt0 < ((Object_Mesh^)s_object)->vertex_array_length_0; cnt0++)
						for(cnt1 = 0; cnt1 < ((Object_Mesh^)s_object)->vertex_array_length_1; cnt1++)
							DrawClippedLine(pen_0, XFormto2D(*(((Object_Mesh^)s_object)->vertices[cnt0, cnt1])), XFormto2D(*(((Object_Mesh^)s_object)->vertices[(cnt0 - 1), cnt1])));
					 for(cnt0 = 0; cnt0 < ((Object_Mesh^)s_object)->vertex_array_length_0; cnt0++)
						for(cnt1 = 1; cnt1 < ((Object_Mesh^)s_object)->vertex_array_length_1; cnt1++)
							DrawClippedLine(pen_0, XFormto2D(*(((Object_Mesh^)s_object)->vertices[cnt0, cnt1])), XFormto2D(*(((Object_Mesh^)s_object)->vertices[cnt0, (cnt1 - 1)])));
					 if(s_object->selected)
						 for(cnt0 = 0; cnt0 < ((Object_Mesh^)s_object)->vertex_array_length_0; cnt0++)
							 for(cnt1 = 0; cnt1 < ((Object_Mesh^)s_object)->vertex_array_length_1; cnt1++)
								DrawPoint(XFormto2D(*(((Object_Mesh^)s_object)->vertices[cnt0, cnt1])));
					 break;
				 }
			 case 10:
				 if((object_creation_state == 46) || (s_object->IsFinalized())){ 
					if(resample) ((Object_Bilinear_Surf^)(s_object))->Sample(global_scale);
					for(((Object_Bilinear_Surf^)(s_object))->s_current_position_00 = 1; ((Object_Bilinear_Surf^)(s_object))->s_current_position_00 < ((Object_Bilinear_Surf^)(s_object))->s_vertex_array_length_00; ((Object_Bilinear_Surf^)(s_object))->s_current_position_00++)
						for(((Object_Bilinear_Surf^)(s_object))->s_current_position_01 = 0; ((Object_Bilinear_Surf^)(s_object))->s_current_position_01 < ((Object_Bilinear_Surf^)(s_object))->s_vertex_array_length_01; ((Object_Bilinear_Surf^)(s_object))->s_current_position_01++)
							DrawClippedLine(pen_0, XFormto2D(*(((Object_Bilinear_Surf^)s_object)->sampled_vertices_0[((Object_Bilinear_Surf^)(s_object))->s_current_position_00, ((Object_Bilinear_Surf^)(s_object))->s_current_position_01])), XFormto2D(*(((Object_Bilinear_Surf^)s_object)->sampled_vertices_0[(((Object_Bilinear_Surf^)(s_object))->s_current_position_00 - 1), ((Object_Bilinear_Surf^)(s_object))->s_current_position_01])));
					for(((Object_Bilinear_Surf^)(s_object))->s_current_position_10 = 1; ((Object_Bilinear_Surf^)(s_object))->s_current_position_10 < ((Object_Bilinear_Surf^)(s_object))->s_vertex_array_length_10; ((Object_Bilinear_Surf^)(s_object))->s_current_position_10++)
						for(((Object_Bilinear_Surf^)(s_object))->s_current_position_11 = 0; ((Object_Bilinear_Surf^)(s_object))->s_current_position_11 < ((Object_Bilinear_Surf^)(s_object))->s_vertex_array_length_11; ((Object_Bilinear_Surf^)(s_object))->s_current_position_11++)
							DrawClippedLine(pen_0, XFormto2D(*(((Object_Bilinear_Surf^)s_object)->sampled_vertices_1[((Object_Bilinear_Surf^)(s_object))->s_current_position_10, ((Object_Bilinear_Surf^)(s_object))->s_current_position_11])), XFormto2D(*(((Object_Bilinear_Surf^)s_object)->sampled_vertices_1[(((Object_Bilinear_Surf^)(s_object))->s_current_position_10 - 1), ((Object_Bilinear_Surf^)(s_object))->s_current_position_11])));
				 }
				 if(s_object->selected){
					 System::Byte cnt0;
					 System::Byte limit;
					 if(s_object->IsFinalized()) limit = 4;
					 else limit = object_creation_state - 42;
					 for(cnt0 = 0; cnt0 < limit; cnt0++) DrawPoint(XFormto2D(*(((Object_Bilinear_Surf^)s_object)->vertices[cnt0])));
				 }
				 break;
			 case 11:
				 {
					 System::UInt32 cnt0, cnt1;
					 if(resample) ((Object_Bezier_Surf^)(s_object))->Sample(global_scale);
					 if(s_object->selected){
						 pen_5->Color = Color::FromArgb(s_object->object_color);
						 if(modification_flag) pen_5->Color = Color::FromArgb(0xFFFFFFFF);
						 for(cnt0 = 1; cnt0 < ((Object_Bezier_Surf^)s_object)->vertex_array_length_0; cnt0++)
							 for(cnt1 = 0; cnt1 < ((Object_Bezier_Surf^)s_object)->vertex_array_length_1; cnt1++)
								DrawClippedLine(pen_5, XFormto2D(*(((Object_Bezier_Surf^)s_object)->vertices[cnt0, cnt1])), XFormto2D(*(((Object_Bezier_Surf^)s_object)->vertices[(cnt0 - 1), cnt1])));
						 for(cnt0 = 0; cnt0 < ((Object_Bezier_Surf^)s_object)->vertex_array_length_0; cnt0++)
							 for(cnt1 = 1; cnt1 < ((Object_Bezier_Surf^)s_object)->vertex_array_length_1; cnt1++)
								DrawClippedLine(pen_5, XFormto2D(*(((Object_Bezier_Surf^)s_object)->vertices[cnt0, cnt1])), XFormto2D(*(((Object_Bezier_Surf^)s_object)->vertices[cnt0, (cnt1 - 1)])));
						 for(cnt0 = 0; cnt0 < ((Object_Mesh^)s_object)->vertex_array_length_0; cnt0++)
							 for(cnt1 = 0; cnt1 < ((Object_Mesh^)s_object)->vertex_array_length_1; cnt1++)
								DrawPoint(XFormto2D(*(((Object_Bezier_Surf^)s_object)->vertices[cnt0, cnt1])));
					 }					 
					 for(((Object_Bezier_Surf^)(s_object))->s_current_position_00 = 1; ((Object_Bezier_Surf^)(s_object))->s_current_position_00 < ((Object_Bezier_Surf^)(s_object))->s_vertex_array_length_00; ((Object_Bezier_Surf^)(s_object))->s_current_position_00++)
						 for(((Object_Bezier_Surf^)(s_object))->s_current_position_01 = 0; ((Object_Bezier_Surf^)(s_object))->s_current_position_01 < ((Object_Bezier_Surf^)(s_object))->s_vertex_array_length_01; ((Object_Bezier_Surf^)(s_object))->s_current_position_01++)
							 DrawClippedLine(pen_0, XFormto2D(*(((Object_Bezier_Surf^)s_object)->sampled_vertices_0[((Object_Bezier_Surf^)(s_object))->s_current_position_00, ((Object_Bezier_Surf^)(s_object))->s_current_position_01])), XFormto2D(*(((Object_Bezier_Surf^)s_object)->sampled_vertices_0[(((Object_Bezier_Surf^)(s_object))->s_current_position_00 - 1), ((Object_Bezier_Surf^)(s_object))->s_current_position_01])));
					 for(((Object_Bezier_Surf^)(s_object))->s_current_position_10 = 1; ((Object_Bezier_Surf^)(s_object))->s_current_position_10 < ((Object_Bezier_Surf^)(s_object))->s_vertex_array_length_10; ((Object_Bezier_Surf^)(s_object))->s_current_position_10++)
						 for(((Object_Bezier_Surf^)(s_object))->s_current_position_11 = 0; ((Object_Bezier_Surf^)(s_object))->s_current_position_11 < ((Object_Bezier_Surf^)(s_object))->s_vertex_array_length_11; ((Object_Bezier_Surf^)(s_object))->s_current_position_11++)
							 DrawClippedLine(pen_0, XFormto2D(*(((Object_Bezier_Surf^)s_object)->sampled_vertices_1[((Object_Bezier_Surf^)(s_object))->s_current_position_10, ((Object_Bezier_Surf^)(s_object))->s_current_position_11])), XFormto2D(*(((Object_Bezier_Surf^)s_object)->sampled_vertices_1[(((Object_Bezier_Surf^)(s_object))->s_current_position_10 - 1), ((Object_Bezier_Surf^)(s_object))->s_current_position_11])));
					 break;
				 }
			 case 12:
				 {
					 System::UInt32 cnt0, cnt1;
					 if(resample) ((Object_BSpline_Surf^)(s_object))->Sample(global_scale);
					 if(s_object->selected){
						 pen_5->Color = Color::FromArgb(s_object->object_color);
						 if(modification_flag) pen_5->Color = Color::FromArgb(0xFFFFFFFF);
						 for(cnt0 = 1; cnt0 < ((Object_BSpline_Surf^)s_object)->vertex_array_length_0; cnt0++)
							 for(cnt1 = 0; cnt1 < ((Object_BSpline_Surf^)s_object)->vertex_array_length_1; cnt1++)
								DrawClippedLine(pen_5, XFormto2D(*(((Object_BSpline_Surf^)s_object)->vertices[cnt0, cnt1])), XFormto2D(*(((Object_BSpline_Surf^)s_object)->vertices[(cnt0 - 1), cnt1])));
						 for(cnt0 = 0; cnt0 < ((Object_BSpline_Surf^)s_object)->vertex_array_length_0; cnt0++)
							 for(cnt1 = 1; cnt1 < ((Object_BSpline_Surf^)s_object)->vertex_array_length_1; cnt1++)
								DrawClippedLine(pen_5, XFormto2D(*(((Object_BSpline_Surf^)s_object)->vertices[cnt0, cnt1])), XFormto2D(*(((Object_BSpline_Surf^)s_object)->vertices[cnt0, (cnt1 - 1)])));
						 for(cnt0 = 0; cnt0 < ((Object_Mesh^)s_object)->vertex_array_length_0; cnt0++)
							 for(cnt1 = 0; cnt1 < ((Object_Mesh^)s_object)->vertex_array_length_1; cnt1++)
								DrawPoint(XFormto2D(*(((Object_BSpline_Surf^)s_object)->vertices[cnt0, cnt1])));
					 }					 
					 for(((Object_BSpline_Surf^)(s_object))->s_current_position_00 = 1; ((Object_BSpline_Surf^)(s_object))->s_current_position_00 < ((Object_BSpline_Surf^)(s_object))->s_vertex_array_length_00; ((Object_BSpline_Surf^)(s_object))->s_current_position_00++)
						 for(((Object_BSpline_Surf^)(s_object))->s_current_position_01 = 0; ((Object_BSpline_Surf^)(s_object))->s_current_position_01 < ((Object_BSpline_Surf^)(s_object))->s_vertex_array_length_01; ((Object_BSpline_Surf^)(s_object))->s_current_position_01++)
							 DrawClippedLine(pen_0, XFormto2D(*(((Object_BSpline_Surf^)s_object)->sampled_vertices_0[((Object_BSpline_Surf^)(s_object))->s_current_position_00, ((Object_BSpline_Surf^)(s_object))->s_current_position_01])), XFormto2D(*(((Object_BSpline_Surf^)s_object)->sampled_vertices_0[(((Object_BSpline_Surf^)(s_object))->s_current_position_00 - 1), ((Object_BSpline_Surf^)(s_object))->s_current_position_01])));
					 for(((Object_BSpline_Surf^)(s_object))->s_current_position_10 = 1; ((Object_BSpline_Surf^)(s_object))->s_current_position_10 < ((Object_BSpline_Surf^)(s_object))->s_vertex_array_length_10; ((Object_BSpline_Surf^)(s_object))->s_current_position_10++)
						 for(((Object_BSpline_Surf^)(s_object))->s_current_position_11 = 0; ((Object_BSpline_Surf^)(s_object))->s_current_position_11 < ((Object_BSpline_Surf^)(s_object))->s_vertex_array_length_11; ((Object_BSpline_Surf^)(s_object))->s_current_position_11++)
							 DrawClippedLine(pen_0, XFormto2D(*(((Object_BSpline_Surf^)s_object)->sampled_vertices_1[((Object_BSpline_Surf^)(s_object))->s_current_position_10, ((Object_BSpline_Surf^)(s_object))->s_current_position_11])), XFormto2D(*(((Object_BSpline_Surf^)s_object)->sampled_vertices_1[(((Object_BSpline_Surf^)(s_object))->s_current_position_10 - 1), ((Object_BSpline_Surf^)(s_object))->s_current_position_11])));
					 break;
				 }
			 case 13:
				 if((object_creation_state > 62) || (s_object->IsFinalized())){ 
					if(resample) ((Object_Bicubic_Surf^)(s_object))->Sample(global_scale);
					for(((Object_Bicubic_Surf^)(s_object))->s_current_position_00 = 1; ((Object_Bicubic_Surf^)(s_object))->s_current_position_00 < ((Object_Bicubic_Surf^)(s_object))->s_vertex_array_length_00; ((Object_Bicubic_Surf^)(s_object))->s_current_position_00++)
						for(((Object_Bicubic_Surf^)(s_object))->s_current_position_01 = 0; ((Object_Bicubic_Surf^)(s_object))->s_current_position_01 < ((Object_Bicubic_Surf^)(s_object))->s_vertex_array_length_01; ((Object_Bicubic_Surf^)(s_object))->s_current_position_01++)
							DrawClippedLine(pen_0, XFormto2D(*(((Object_Bicubic_Surf^)s_object)->sampled_vertices_0[((Object_Bicubic_Surf^)(s_object))->s_current_position_00, ((Object_Bicubic_Surf^)(s_object))->s_current_position_01])), XFormto2D(*(((Object_Bicubic_Surf^)s_object)->sampled_vertices_0[(((Object_Bicubic_Surf^)(s_object))->s_current_position_00 - 1), ((Object_Bicubic_Surf^)(s_object))->s_current_position_01])));
					for(((Object_Bicubic_Surf^)(s_object))->s_current_position_10 = 1; ((Object_Bicubic_Surf^)(s_object))->s_current_position_10 < ((Object_Bicubic_Surf^)(s_object))->s_vertex_array_length_10; ((Object_Bicubic_Surf^)(s_object))->s_current_position_10++)
						for(((Object_Bicubic_Surf^)(s_object))->s_current_position_11 = 0; ((Object_Bicubic_Surf^)(s_object))->s_current_position_11 < ((Object_Bicubic_Surf^)(s_object))->s_vertex_array_length_11; ((Object_Bicubic_Surf^)(s_object))->s_current_position_11++)
							DrawClippedLine(pen_0, XFormto2D(*(((Object_Bicubic_Surf^)s_object)->sampled_vertices_1[((Object_Bicubic_Surf^)(s_object))->s_current_position_10, ((Object_Bicubic_Surf^)(s_object))->s_current_position_11])), XFormto2D(*(((Object_Bicubic_Surf^)s_object)->sampled_vertices_1[(((Object_Bicubic_Surf^)(s_object))->s_current_position_10 - 1), ((Object_Bicubic_Surf^)(s_object))->s_current_position_11])));
				 }
				 if(s_object->selected){
					 System::Byte cnt0;
					 System::Byte limit;
					 if((s_object->IsFinalized()) || (object_creation_state > 62)) limit = 4;
					 else limit = object_creation_state - 59;
					 for(cnt0 = 0; cnt0 < limit; cnt0++) DrawPoint(XFormto2D(*(((Object_Bicubic_Surf^)s_object)->vertices[cnt0])));
					 pen_6->Color = Color::FromArgb(s_object->object_color);
					 if(modification_flag) pen_6->Color = Color::FromArgb(0xFFFFFFFF);
					 for(cnt0 = 0; cnt0 < 4; cnt0++){
						DrawClippedLine(pen_6, XFormto2D(*(((Object_Bicubic_Surf^)s_object)->vertices[cnt0])), XFormto2D(((Object_Bicubic_Surf^)s_object)->vertices[cnt0 + 4] + *(((Object_Bicubic_Surf^)s_object)->vertices[cnt0])));
						DrawClippedLine(pen_6, XFormto2D(*(((Object_Bicubic_Surf^)s_object)->vertices[cnt0])), XFormto2D(((Object_Bicubic_Surf^)s_object)->vertices[cnt0 + 8] + *(((Object_Bicubic_Surf^)s_object)->vertices[cnt0])));
						DrawClippedLine(pen_6, XFormto2D(*(((Object_Bicubic_Surf^)s_object)->vertices[cnt0])), XFormto2D(((Object_Bicubic_Surf^)s_object)->vertices[cnt0 + 12] + *(((Object_Bicubic_Surf^)s_object)->vertices[cnt0])));
					 }
				 }
				 break;
			 }
		 }

		 void DrawClippedLine(System::Drawing::Pen^ pen, System::Drawing::Point% pnt0, System::Drawing::Point% pnt1){
			 if(IsPointInPane(pnt0)){
				 if(IsPointInPane(pnt1)) pe->Graphics->DrawLine(pen, pnt0, pnt1);
				 else pe->Graphics->DrawLine(pen, pnt0, ClipLine(pnt0, pnt1, 1));
			 }
			 else if(IsPointInPane(pnt1)) pe->Graphics->DrawLine(pen, pnt1, ClipLine(pnt1, pnt0, 1));
			 else if(PointCompatibility(pnt0, pnt1)){
				 System::Drawing::Point temp_pnt = ClipLine(pnt0, pnt1, 1);
				 pe->Graphics->DrawLine(pen, temp_pnt, ClipLine(pnt1, pnt0, 0));
			 }
		 }

		 System::Drawing::Point ClipLine(System::Drawing::Point% pnt0, System::Drawing::Point% pnt1, System::Boolean mode){
			 System::Double param;
			 if((pnt1.X - pnt0.X)){
				 param = (System::Double)(PANE_LEFT1 - pnt0.X) / (System::Double)(pnt1.X - pnt0.X);
				 if((param >= 0) && (param <= 1)){
					 System::Drawing::Point temp_pnt = System::Drawing::Point(Math::Round(((1 - param) * (System::Double)pnt0.X + param * (System::Double)pnt1.X)), Math::Round(((1 - param) * (System::Double)pnt0.Y + param * (System::Double)pnt1.Y)));
					 if(IsPointInPane(temp_pnt)){
						 if(mode) return temp_pnt;
						 else mode = true;
					 }
				 }
			 }
			 if((pnt1.X - pnt0.X)){
				 param = (System::Double)(PANE_RIGHTM2 - pnt0.X) / (System::Double)(pnt1.X - pnt0.X);
				 if((param >= 0) && (param <= 1)){
					 System::Drawing::Point temp_pnt = System::Drawing::Point(Math::Round(((1 - param) * (System::Double)pnt0.X + param * (System::Double)pnt1.X)), Math::Round(((1 - param) * (System::Double)pnt0.Y + param * (System::Double)pnt1.Y)));
					 if(IsPointInPane(temp_pnt)){
						 if(mode) return temp_pnt;
						 else mode = true;
					 }
				 }
			 }
			 if((pnt1.Y - pnt0.Y)){
				 param = (System::Double)(PANE_TOP1 - pnt0.Y) / (System::Double)(pnt1.Y - pnt0.Y);
				 if((param >= 0) && (param <= 1)){
					 System::Drawing::Point temp_pnt = System::Drawing::Point(Math::Round(((1 - param) * (System::Double)pnt0.X + param * (System::Double)pnt1.X)), Math::Round(((1 - param) * (System::Double)pnt0.Y + param * (System::Double)pnt1.Y)));
					 if(IsPointInPane(temp_pnt) && mode) return temp_pnt;
				 }
			 }
			 param = (System::Double)(PANE_BOTTOMM2 - pnt0.Y) / (System::Double)(pnt1.Y - pnt0.Y);
			 System::Drawing::Point temp_pnt = System::Drawing::Point(Math::Round(((1 - param) * (System::Double)pnt0.X + param * (System::Double)pnt1.X)), Math::Round(((1 - param) * (System::Double)pnt0.Y + param * (System::Double)pnt1.Y)));
			 return temp_pnt;
		 }

		 void DrawPoint(System::Drawing::Point point_arg){
			 DrawClippedLine(pen_0, point_arg - System::Drawing::Size(5, 0), point_arg + System::Drawing::Size(5, 0));
			 DrawClippedLine(pen_0, point_arg - System::Drawing::Size(0, 5), point_arg + System::Drawing::Size(0, 5));
		 }

		 void PanelSpecifier2(void){
			 switch(object_creation_state){
			 case 2:
			 	 label5->Text = "Indicate end position";
				 break;
			 case 4: //polyline
			 case 17: //bezier
			 case 22: //cubic spline
			 case 35: //bspline
			 case 39: //mesh
			 case 48: //bezier surf
			 case 54: //bspline surf
				 label5->Text = "Indicate next position";
				 break;
			 case 5: //polyline
			 case 18: //bezier
			 case 23: //cubic spline
			 case 36: //bspline
			 case 40: //mesh
			 case 41: //mesh
			 case 49: //bezier surf
			 case 50: //bezier surf
			 case 55: //bspline surf
			 case 56: //bspline surf
				 button4->Visible = true;
				 break;
			 case 42: //mesh
			 case 51: //bezier surf
			 case 57: //bspline surf
				 button4->Visible = false;
				 break;
			 case 64:
			 case 68:
			 case 72:
				 label5->Text = "Indicate 1st corner";
				 break;
			 case 44:
			 case 61:
			 case 65:
			 case 69:
			 case 73:
				 label5->Text = "Indicate 2nd corner";
				 break;
			 case 45:
			 case 62:
			 case 66:
			 case 70:
			 case 74:
				 label5->Text = "Indicate 3rd corner";
				 break;
			 case 46:
			 case 63:
			 case 67:
			 case 71:
			 case 75:
				 label5->Text = "Indicate 4th corner";
				 break;
			 case 21:
				 label5->Text = "Indicate first point derivative";
				 break;
			 case 26:
				 label5->Text = "Indicate directrix end position";
				 break;
			 case 27:
				 label5->Text = "Indicate focus";
				 break;
			 case 28:
				 textBox7->Text = "0";
				 label9->Text = "Indicate start position x";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 3;
				 panelarray[3]->Visible = true;
				 click_permit = false;
				 break;
			 case 31:
				 label5->Text = "Indicate second point";
				 break;
			 case 32:
				 label5->Text = "Indicate third point";
				 break;
			 case 77:
				 label5->Text = "Indicate first asymptote direction";
				 break;
			 case 78:
				 label5->Text = "Indicate second asymptote direction";
				 break;
			 case 79:
				 textBox7->Text = "1";
				 label9->Text = "Indicate asymptotic behavior scale";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 3;
				 panelarray[3]->Visible = true;
				 click_permit = false;
				 break;
			 }
			 switch(object_creation_state){
			 case 64:
			 case 65:
			 case 66:
			 case 67:
				 label5->Text += " derivative in first direction";
				 break;
			 case 68:
			 case 69:
			 case 70:
			 case 71:
				 label5->Text += " derivative in second direction";
				 break;
			 case 72:
			 case 73:
			 case 74:
			 case 75:
				 label5->Text += " twist derivative";
				 break;
			 }
			 switch(object_modification_state){
			 case 8:
				 click_permit = false;
				 temp_vector_1 = vector3D(1, 1, 1);
				 label15->Text = "sX=";
				 label16->Text = "sY=";
				 label17->Text = "sZ=";
				 textBox9->Text = "1";
				 textBox10->Text = "1";
				 textBox11->Text = "1";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 7;
				 panelarray[7]->Visible = true;
				 break;
			 case 11:
				 label5->Text = "Indicate second point on rotation axis";
				 break;
			 case 12:
				 click_permit = false;
				 object_rotation = 0;
				 textBox7->Text = "0";
				 label9->Text = "Indicate rotation angle";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 3;
				 panelarray[3]->Visible = true;
				 break;
			 }
		 }

		 void Panel5Buttons(System::Byte mode){
			 panelarray[activepanel]->Visible = false;
			 activepanel = 2;
			 panelarray[2]->Visible = true;
			 object_list_header->AddObject(gcnew Object_Cubic_Spline(pen_color));
			 ((Object_Cubic_Spline^)(object_list_header->GetNext()))->AddVertex(vector3D());
			 ((Object_Cubic_Spline^)(object_list_header->GetNext()))->end_condition_mode = mode;
			 object_creation_state = 20;
			 click_permit = true;
		 }

		 void Panel6Buttons(void){
			 if(object_creation_state == 33){
				object_list_header->AddObject(gcnew Object_BSpline(pen_color));
				((Object_BSpline^)(object_list_header->GetNext()))->BSplineAddVertex(vector3D());
			 }
			 else{
				object_list_header->AddObject(gcnew Object_BSpline_Surf(pen_color));
				((Object_BSpline_Surf^)(object_list_header->GetNext()))->BSplineAddVertex(vector3D());
			 }
			 label5->Text = "Indicate start position";
			 panelarray[activepanel]->Visible = false;
			 activepanel = 2;
			 panelarray[2]->Visible = true;
			 object_creation_state++;
			 click_permit = true;
		 }

	/******************************************************************
	******************User-Defined Functions - End*********************
    *******************************************************************/

	private: System::Void exitProgramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				exit(0);
			 }

	private: System::Void penColorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				PanelEnter();
				panel_controller[0] = 0;
				textBox1->Text = Convert::ToString((pen_color<<8)>>24);
				textBox2->Text = Convert::ToString((pen_color<<16)>>24);
				textBox3->Text = Convert::ToString((pen_color<<24)>>24);
				panel_controller[0] = 1;
				panel_specifier[0] = 0;
				button10->Visible = false;
				panelarray[activepanel]->Visible = false;
				activepanel = 1;
				panelarray[1]->Visible = true;
			 }

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				PanelEscape();
			 }

	private: System::Void backgroundColorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				PanelEnter();
				panel_controller[0] = 0;
				textBox1->Text = Convert::ToString((brush_color_1<<8)>>24);
				textBox2->Text = Convert::ToString((brush_color_1<<16)>>24);
				textBox3->Text = Convert::ToString((brush_color_1<<24)>>24);
				panel_controller[0] = 1;
				panel_specifier[0] = 1;
				panelarray[activepanel]->Visible = false;
				activepanel = 1;
				panelarray[1]->Visible = true;
				button10->Text = "Top";
				button10->Visible = true;
			 }

	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(panel_controller[0]){
					 try{
						 System::UInt32 temp_color_holder;
						 if(panel_specifier[0] == 1) temp_color_holder = brush_color_1;
						 else if(panel_specifier[0] == 2) temp_color_holder = brush_color_0;
						 else if(object_modification_state == 3) temp_color_holder = selected_object->object_color;
						 else temp_color_holder = pen_color;
						 System::UInt16 input_num = Convert::ToUInt16(textBox1->Text);
						 if(input_num>254){
							 textBox1->Text = "255";
							 temp_color_holder |= 0x00FF0000;
						 }
						 else{
							 temp_color_holder &= 0xFF00FFFF;
							 temp_color_holder |= input_num<<16;
						 }
						 if(panel_specifier[0] == 1){
							 brush_color_1 = temp_color_holder;
							 brush_colors[1] = Color::FromArgb(brush_color_1);
							 brush_0->LinearColors = brush_colors;
							 Paint(pe);
						 }
						 else if(panel_specifier[0] == 2){
							 brush_color_0 = temp_color_holder;
							 brush_colors[0] = Color::FromArgb(brush_color_0);
							 brush_0->LinearColors = brush_colors;
							 Paint(pe);
						 }
						 else if(object_modification_state == 3){
							 selected_object->object_color = temp_color_holder;
							 Paint(pe);
						 }
						 else{
							 pen_color = temp_color_holder;
							 pen_0->Color = Color::FromArgb(pen_color);
						 }
					 }
					 catch (System::FormatException^){
						 textBox1->Text = "0";
						 if(panel_specifier[0] == 1) brush_color_1 &= 0xFF00FFFF;
						 else if(panel_specifier[0] == 2) brush_color_0 &= 0xFF00FFFF;
						 else if(object_modification_state == 3) selected_object->object_color &= 0xFF00FFFF;
						 else pen_color &= 0xFF00FFFF;
					 }
					 catch (System::OverflowException^){
						 textBox1->Text = "0";
						 if(panel_specifier[0] == 1) brush_color_1 &= 0xFF00FFFF;
						 else if(panel_specifier[0] == 2) brush_color_0 &= 0xFF00FFFF;
						 else if(object_modification_state == 3) selected_object->object_color &= 0xFF00FFFF;
						 else pen_color &= 0xFF00FFFF;
					 }
				 }
			 }

	private: System::Void textBox1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				System::Int16 input_num = Convert::ToInt16(textBox1->Text);
				if(e->Delta > 0) input_num++;
				else input_num--;
				textBox1->Text = Convert::ToString(input_num);
			 }

	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				if(panel_controller[0]){
					 try{
						 System::UInt32 temp_color_holder;
						 if(panel_specifier[0] == 1) temp_color_holder = brush_color_1;
						 else if(panel_specifier[0] == 2) temp_color_holder = brush_color_0;
						 else if(object_modification_state == 3) temp_color_holder = selected_object->object_color;
						 else temp_color_holder = pen_color;
						 System::UInt16 input_num = Convert::ToUInt16(textBox2->Text);					 
						 if(input_num>254){
							 textBox2->Text = "255";
							 temp_color_holder |= 0x0000FF00;
						 }
						 else{
							 temp_color_holder &= 0xFFFF00FF;
							 temp_color_holder |= input_num << 8;
						 }
						 if(panel_specifier[0] == 1){
							 brush_color_1 = temp_color_holder;
							 brush_colors[1] = Color::FromArgb(brush_color_1);
							 brush_0->LinearColors = brush_colors;
							 Paint(pe);
						 }
						 else if(panel_specifier[0] == 2){
							 brush_color_0 = temp_color_holder;
							 brush_colors[0] = Color::FromArgb(brush_color_0);
							 brush_0->LinearColors = brush_colors;
							 Paint(pe);
						 }
						 else if(object_modification_state == 3){
							 selected_object->object_color = temp_color_holder;
							 Paint(pe);
						 }
						 else{
							 pen_color = temp_color_holder;
							 pen_0->Color = Color::FromArgb(pen_color);
						 }
					 }
					 catch (System::FormatException^){
						 textBox2->Text = "0";
						 if(panel_specifier[0] == 1) brush_color_1 &= 0xFFFF00FF;
						 else if(panel_specifier[0] == 2) brush_color_0 &= 0xFFFF00FF;
						 else if(object_modification_state == 3) selected_object->object_color &= 0xFFFF00FF;
						 else pen_color &= 0xFFFF00FF;
					 }
					 catch (System::OverflowException^){
						 textBox2->Text = "0";
						 if(panel_specifier[0] == 1) brush_color_1 &= 0xFFFF00FF;
						 else if(panel_specifier[0] == 2) brush_color_0 &= 0xFFFF00FF;
						 else if(object_modification_state == 3) selected_object->object_color &= 0xFFFF00FF;
						 else pen_color &= 0xFFFF00FF;
					 }
				 }
			}

	private: System::Void textBox2_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 System::Int16 input_num = Convert::ToInt16(textBox2->Text);
				 if(e->Delta > 0) input_num++;
				 else input_num--;
				 textBox2->Text = Convert::ToString(input_num);
		 }

	private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(panel_controller[0]){
					 try{
						 System::UInt32 temp_color_holder;
						 if(panel_specifier[0] == 1) temp_color_holder = brush_color_1;
						 else if(panel_specifier[0] == 2) temp_color_holder = brush_color_0;
						 else if(object_modification_state == 3) temp_color_holder = selected_object->object_color;
						 else temp_color_holder = pen_color;
						 System::UInt16 input_num = Convert::ToUInt16(textBox3->Text);
						 if(input_num>254){
							 textBox3->Text = "255";
							 temp_color_holder |= 0x000000FF;
					     }
						 else{
							 temp_color_holder &= 0xFFFFFF00;
							 temp_color_holder |= input_num;
						 }
						 if(panel_specifier[0] == 1){
							 brush_color_1 = temp_color_holder;
							 brush_colors[1] = Color::FromArgb(brush_color_1);
							 brush_0->LinearColors = brush_colors;
							 Paint(pe);
						 }
						 else if(panel_specifier[0] == 2){
							 brush_color_0 = temp_color_holder;
							 brush_colors[0] = Color::FromArgb(brush_color_0);
							 brush_0->LinearColors = brush_colors;
							 Paint(pe);
						 }
						 else if(object_modification_state == 3){
							 selected_object->object_color = temp_color_holder;
							 Paint(pe);
						 }
						 else{
							 pen_color = temp_color_holder;
							 pen_0->Color = Color::FromArgb(pen_color);
						 }						 
					 }
					 catch (System::FormatException^){
						 textBox3->Text = "0";
						 if(panel_specifier[0] == 1) brush_color_1 &= 0xFFFFFF00;
						 else if(panel_specifier[0] == 2) brush_color_0 &= 0xFFFFFF00;
						 else if(object_modification_state == 3) selected_object->object_color &= 0xFFFFFF00;
						 else pen_color &= 0xFFFFFF00;
					 }
					 catch (System::OverflowException^){
						 textBox3->Text = "0";
						 if(panel_specifier[0] == 1) brush_color_1 &= 0xFFFFFF00;
						 else if(panel_specifier[0] == 2) brush_color_0 &= 0xFFFFFF00;
						 else if(object_modification_state == 3) selected_object->object_color &= 0xFFFFFF00;
						 else pen_color &= 0xFFFFFF00;
					 }
				 }
			 }

	private: System::Void textBox3_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				System::Int16 input_num = Convert::ToInt16(textBox3->Text);
				if(e->Delta > 0) input_num++;
				else input_num--;
				textBox3->Text = Convert::ToString(input_num);
			}

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 paint_lock = true;
				 preview_lock = true;
			}

	private: System::Void Form1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
					if(IsCursorInPane()){
						this->Cursor->Current = Cursors::Cross;
						StatusUpdate();
						if(click_permit)
						if(object_list_header->GetNext() != object_list_header)
							if(!(object_list_header->GetNext()->IsFinalized())){							
								PreviewPoint(!click_key_switch);
								preview_lock = false;
							}
					}
					if(drag_control){
						click_control = false;
						delta = GetCurPos() - System::Drawing::Size(prev_location);
						radius = prev_location - System::Drawing::Size((System::Int32)(global_shift_x), (System::Int32)(global_shift_y));
						delta_theta = Magnitude2D(delta) / (Magnitude2D(radius) + 40.0);
						rotator = (view_x * (-delta.Y)) + (-view_y * (delta.X)) // the part of rotator which lies in the view plane
								- view_z * (System::Double)((radius.Y * delta.X) - (radius.X * delta.Y)) / (Magnitude2D(radius) + 40.0); // the part of rotator which is orthogonal to the view plane
						view_x.Rotate(rotator, (System::Double)(delta_theta));
						view_y.Rotate(rotator, (System::Double)(delta_theta));
						//Gram-Schmidt Algorithm
						view_x.Unit();
						view_y -= view_x * view_y.DotProduct(view_x);						 
						view_y.Unit();
						view_z = view_x.XProduct(view_y);
						prev_location = GetCurPos(); 
						Paint(pe);						 
					}
			 }

	private: System::Void Form1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {	 
				if(IsCursorInPane()){
					if(e->Delta > 0) global_scale *= 1.1;
					else global_scale /= 1.1;
					toolStripStatusLabel4->Text = (global_scale).ToString("S=#.0000e+00");
					resample = true;
					Paint(pe);
					StatusUpdate();
				}
				switch(object_modification_state){
				case 1:
				case 2:
				case 4:
					if(!IsCursorInPane()){
						selected_object->selected = false;
						if(e->Delta > 0){
							selected_object = selected_object->GetNext();
							if(selected_object == object_list_header) selected_object = selected_object->GetNext();
						}
						else{
							selected_object = selected_object->GetPrev();
							if(selected_object == object_list_header) selected_object = selected_object->GetPrev();
						}
						selected_object->selected = true;
						Paint(pe);
					}
					break;
				}
			 }

	private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {	 
				 if(IsCursorInPane()){
					  this->Cursor->Current = Cursors::Cross;
					  if((System::UInt32)this->MouseButtons == 1048576){
						  click_control = true;						 
						  drag_control = true;
						  prev_location = GetCurPos();
					 }
				 }
			 }

	private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if(IsCursorInPane()){
					 this->Cursor->Current = Cursors::Cross;
					 if(click_permit && click_key_switch && (object_creation_state || object_modification_state) && click_control){
						 AddPoint(0);
						 PanelSpecifier2();
					 }
				 }
				 if(!(((System::UInt32)this->MouseButtons << 11) >> 31))
					drag_control = false;
			 }

	private: System::Void lineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Line(pen_color));
				 label5->Text = "Indicate start position";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 object_creation_state = 1;
				 click_permit = true;
			 }

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEscape();
			 }

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				  if(click_key_switch){
					  click_key_switch = false;
					  button3->Text = "Cursor";
					  textBox6->Text = "0";
					  textBox5->Text = "0";
					  textBox4->Text = "0";
					  point_argument.p[0] = 0;
					  point_argument.p[1] = 0;
					  point_argument.p[2] = 0;
					  PreviewPoint(1);
					  textBox4->Visible = true;
					  textBox5->Visible = true;
					  textBox6->Visible = true;
					  textBox8->Visible = false;
					  label6->Visible = true;
					  label7->Visible = true;
					  label8->Visible = true;
					  label10->Visible = false;
				  }				 
				  else{
					  button3->Text = "Key In";
					  label6->Visible = false;
					  label7->Visible = false;
					  label8->Visible = false;
					  label10->Visible = true;
					  textBox4->Visible = false;
					  textBox5->Visible = false;
					  textBox6->Visible = false;
					  textBox8->Visible = true;
					  click_key_switch = true;
					  Paint(pe);
				  }
				  				  
			 }

	private: System::Void textBox6_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 try{
					 point_argument.p[0] = Convert::ToDouble(textBox6->Text);
					 if(object_creation_state) PreviewPoint(1);
				 }
				 catch (System::FormatException^){
					 textBox6->Text = "0";
					 point_argument.p[0] = 0;
				 }
				 catch (System::OverflowException^){
					 textBox6->Text = "0";
					 point_argument.p[0] = 0;
				 }
			 }

	private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 try{
					 point_argument.p[1] = Convert::ToDouble(textBox5->Text);
					 if(object_creation_state) PreviewPoint(1);
				 }
				 catch (System::FormatException^){
					 textBox5->Text = "0";
					 point_argument.p[1] = 0;
				 }
				 catch (System::OverflowException^){
					 textBox5->Text = "0";
					 point_argument.p[1] = 0;
				 }
			 }

	private: System::Void textBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 try{
					 point_argument.p[2] = Convert::ToDouble(textBox4->Text);
					 if(object_creation_state) PreviewPoint(1);
				 }
				 catch (System::FormatException^){
					 textBox4->Text = "0";
					 point_argument.p[2] = 0;
				 }
				 catch (System::OverflowException^){
					 textBox4->Text = "0";
					 point_argument.p[2] = 0;
				 }
			 }

	private: System::Void topViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 view_x = vector3D(1, 0, 0);
				 view_y = vector3D(0, 1, 0);
				 view_z = vector3D(0, 0, 1);
				 Paint(pe);
			 }

	private: System::Void frontViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 view_x = vector3D(1, 0, 0);
				 view_y = vector3D(0, 0, 1);
				 view_z = vector3D(0, -1, 0);
				 Paint(pe);
			 }

	private: System::Void rightViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 view_x = vector3D(0, 1, 0);
				 view_y = vector3D(0, 0, 1);
				 view_z = vector3D(1, 0, 0);
				 Paint(pe);
			 }

	private: System::Void bottomViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 view_x = vector3D(1, 0, 0);
				 view_y = vector3D(0, -1, 0);
				 view_z = vector3D(0, 0, -1);
				 Paint(pe);
			 }

	private: System::Void backViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 view_x = vector3D(-1, 0, 0);
				 view_y = vector3D(0, 0, 1);
				 view_z = vector3D(0, 1, 0);
				 Paint(pe);
			 }

	private: System::Void leftViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 view_x = vector3D(0, -1, 0);
				 view_y = vector3D(0, 0, 1);
				 view_z = vector3D(-1, 0, 0);
				 Paint(pe);
			 }

	private: System::Void isometricViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 view_x = vector3D((R2 / 2), (R2 / 2), 0);
				 view_y = vector3D((-(R2 * R3) / 6), ((R2 * R3) / 6), (R2 / R3));
				 view_z = vector3D((R3 / 3), -(R3 / 3), (R3 / 3));
				 Paint(pe);
			 }

	private: System::Void polylineStringToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_list_header->AddObject(gcnew Object_PolyLine(pen_color));
				 label5->Text = "Indicate start position";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 ((Object_PolyLine^)(object_list_header->GetNext()))->AddVertex(vector3D());
				 object_creation_state = 3;
				 click_permit = true;
			 }

	private: System::Void cubicSplineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 label5->Text = "Indicate start position";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 4;
				 panelarray[4]->Visible = true;
				 object_creation_state = 19;
			 }

	private: System::Void textBox6_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if(e->KeyChar == 0x0D) textBox5->Focus();
			 }

	private: System::Void textBox5_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if(e->KeyChar == 0x0D) textBox4->Focus();
			 }

	private: System::Void textBox4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if(e->KeyChar == 0x0D){ 
					 AddPoint(1);
					 PanelSpecifier2();
					 textBox6->Text = "0";
					 textBox5->Text = "0";
					 textBox4->Text = "0";
					 textBox6->Focus();
				 }
			 }

	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) { // Accept Button
				 button4->Visible = false;
				 if((object_list_header->GetNext()->GetObjTypeId() == 6) && (!(((Object_Cubic_Spline^)(object_list_header->GetNext()))->end_condition_mode))){
					if(((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position != ((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertex_array_max_length)
						delete ((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertices[((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position];
					((Object_Cubic_Spline^)(object_list_header->GetNext()))->current_position--;
					((Object_Cubic_Spline^)(object_list_header->GetNext()))->vertex_array_length--;
					object_creation_state = 24;
					label5->Text = "Indicate end point derivative";
				 }
				 else switch(object_creation_state){
				 case 36:
					 object_creation_state++;
					 click_permit = false;
					 ((Object_BSpline^)(object_list_header->GetNext()))->current_position -= 2;
					 ((Object_BSpline^)(object_list_header->GetNext()))->ClearExtraSpace();
					 ((Object_BSpline^)(object_list_header->GetNext()))->order--;
					 ((Object_BSpline^)(object_list_header->GetNext()))->KnotUpdate();
					 ((Object_BSpline^)(object_list_header->GetNext()))->Sample(global_scale);
					 textBox7->Text = Convert::ToString(((Object_BSpline^)(object_list_header->GetNext()))->order);
					 label9->Text = "Indicate order of the curve";
					 panelarray[activepanel]->Visible = false;
					 activepanel = 3;
					 panelarray[3]->Visible = true;
					 break;
				 case 40:
					 object_creation_state += 2;
					 ((Object_Mesh^)(object_list_header->GetNext()))->ClearExtraSpace();
					 ((Object_Mesh^)(object_list_header->GetNext()))->vertex_mode = true;
					 ((Object_Mesh^)(object_list_header->GetNext()))->AddVertex(vector3D());
					 break;
				 case 49:
					 object_creation_state += 2;
					 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->ClearExtraSpace();
					 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->vertex_mode = true;
					 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->AddVertex(vector3D());
					 break;
				 case 55:
					 object_creation_state += 2;
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->ClearExtraSpace();
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_0--;
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->KnotUpdate0();
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->vertex_mode = true;
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->BSplineAddVertex(vector3D());
					 break;
				 case 56:
					 object_creation_state += 2;
					 click_permit = false;
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->ClearExtraSpace();
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_1--;
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->KnotUpdate1();
					 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
					 textBox7->Text = Convert::ToString(((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_0);
					 label9->Text = "Indicate order in first dimension";
					 panelarray[activepanel]->Visible = false;
					 activepanel = 3;
					 panelarray[3]->Visible = true;
					 break;
				 default:
					object_creation_state = 255;
					AddPoint(0);
				 }
			 }

	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEscape();
			 }

	private: System::Void polygonToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 textBox7->Text = "0";
				 object_list_header->AddObject(gcnew Object_Polygon(pen_color));
				 label9->Text = "Indicate number of sides";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 3;
				 panelarray[3]->Visible = true;
				 object_creation_state = 6;
			 }

	private: System::Void textBox8_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 		 try{
					 construction_depth = Convert::ToDouble(textBox8->Text);
					 toolStripStatusLabel3->Text = Convert::ToString(XFormto3D(GetCurPos()).p[2]);
				 }
				 catch (System::FormatException^){
					 textBox8->Text = "0";
					 construction_depth = 0;
				 }
				 catch (System::OverflowException^){
					 textBox8->Text = "0";
					 construction_depth = 0;
				 }
			 }

	private: System::Void textBox7_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 switch(object_creation_state){
					 case 6:
		 				 try{
							 Convert::ToUInt16(textBox7->Text);
						 }
						 catch (System::FormatException^){
							 textBox7->Text = "0";
						 }
						 catch (System::OverflowException^){
							 textBox7->Text = "0";
						 }
						 break;
					 case 7:
					 case 8:
					 case 10:
					 case 12:
					 case 13:
					 case 14:
					 case 28:
					 case 29:
					 case 79:
					 case 80:
		 				 try{
							 Convert::ToDouble(textBox7->Text);
						 }
						 catch (System::FormatException^){
							 textBox7->Text = "0";
						 }
						 catch (System::OverflowException^){
							 textBox7->Text = "0";
						 }
						 break;
					 case 37:{
		 					 try{
								 System::UInt32 temp = Convert::ToUInt32(textBox7->Text);
								 if((temp > 1) && (temp <= ((Object_BSpline^)(object_list_header->GetNext()))->vertex_array_length)){
									 ((Object_BSpline^)(object_list_header->GetNext()))->order = temp;
									 ((Object_BSpline^)(object_list_header->GetNext()))->KnotUpdate();
									 ((Object_BSpline^)(object_list_header->GetNext()))->Sample(global_scale);
									 Paint(pe);
								 }
								 else textBox7->Text = Convert::ToString(((Object_BSpline^)(object_list_header->GetNext()))->order);
							 }
							 catch (System::FormatException^){
								 textBox7->Text = Convert::ToString(((Object_BSpline^)(object_list_header->GetNext()))->order);
							 }
							 catch (System::OverflowException^){
								 textBox7->Text = Convert::ToString(((Object_BSpline^)(object_list_header->GetNext()))->order);
							 }
							 break;
						 }
					 case 58:{
		 					 try{
								 System::UInt32 temp = Convert::ToUInt32(textBox7->Text);
								 if((temp > 1) && (temp <= ((Object_BSpline_Surf^)(object_list_header->GetNext()))->vertex_array_length_0)){
									 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_0 = temp;
									 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->KnotUpdate0();
									 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
									 Paint(pe);
								 }
								 else textBox7->Text = Convert::ToString(((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_0);
							 }
							 catch (System::FormatException^){
								 textBox7->Text = Convert::ToString(((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_0);
							 }
							 catch (System::OverflowException^){
								 textBox7->Text = Convert::ToString(((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_0);
							 }
							 break;
						 }
					 case 59:{
		 					 try{
								 System::UInt32 temp = Convert::ToUInt32(textBox7->Text);
								 if((temp > 1) && (temp <= ((Object_BSpline_Surf^)(object_list_header->GetNext()))->vertex_array_length_1)){
									 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_1 = temp;
									 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->KnotUpdate1();
									 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
									 Paint(pe);
								 }
								 else textBox7->Text = Convert::ToString(((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_1);
							 }
							 catch (System::FormatException^){
								 textBox7->Text = Convert::ToString(((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_1);
							 }
							 catch (System::OverflowException^){
								 textBox7->Text = Convert::ToString(((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_1);
							 }
							 break;
						 }
				 }
				 switch(object_creation_state){
					 case 28:
						 ((Object_Parabola^)(object_list_header->GetNext()))->start_x = Convert::ToDouble(textBox7->Text);
						 PreviewPoint(0);
						 break;
					 case 29:
						 ((Object_Parabola^)(object_list_header->GetNext()))->x_difference = Convert::ToDouble(textBox7->Text) - ((Object_Parabola^)(object_list_header->GetNext()))->start_x;
						 ((Object_Parabola^)(object_list_header->GetNext()))->ArcLengthUpdate();
						 PreviewPoint(0);
						 break;
					 case 80:
						 {
							System::Double temp = Convert::ToDouble(textBox7->Text) / ((Object_Hyperbola^)(object_list_header->GetNext()))->asymptotic_scale;
							((Object_Hyperbola^)(object_list_header->GetNext()))->start_theta = Math::Log(temp + Math::Sqrt(Math::Pow(temp, 2) + 1));
							PreviewPoint(0);
						 break;
						 }
					 case 81:
						 {
							System::Double temp = Convert::ToDouble(textBox7->Text) / ((Object_Hyperbola^)(object_list_header->GetNext()))->asymptotic_scale;
							((Object_Hyperbola^)(object_list_header->GetNext()))->theta_difference = Math::Log(temp + Math::Sqrt(Math::Pow(temp, 2) + 1)) - ((Object_Hyperbola^)(object_list_header->GetNext()))->start_theta;
							((Object_Hyperbola^)(object_list_header->GetNext()))->ArcLengthUpdate();
							PreviewPoint(0);
							break;
						 }
				 }
				 if(object_modification_state == 12){
					 System::Double rotation;
		 			 try{
						 rotation = Convert::ToDouble(textBox7->Text);
					 }
					 catch (System::FormatException^){
						 rotation = 0;
						 textBox7->Text = "0";
					 }
					 catch (System::OverflowException^){
						 rotation = 0;
						 textBox7->Text = "0";
					 }
					 rotation -= object_rotation;
					 object_rotation += rotation;
					 selected_object->Rotate(temp_vector_0, temp_vector_1, rotation, global_scale);
					 Paint(pe);
				 }
			 }

	private: System::Void textBox7_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if(e->KeyChar == 0x0D){
					 switch(object_creation_state){
						 case 6:
							 ((Object_Polygon^)(object_list_header->GetNext()))->vertex_array_length = Convert::ToUInt32(textBox7->Text);
							 if(((Object_Polygon^)(object_list_header->GetNext()))->vertex_array_length < 3) break;
							 label9->Text = "Indicate rotation angle";
							 textBox7->Text = "0";
							 object_creation_state++;
							 break;
						 case 7:
							 ((Object_Polygon^)(object_list_header->GetNext()))->polygon_rotation = Convert::ToDouble(textBox7->Text);
							 label9->Text = "Indicate size";
							 textBox7->Text = "0";
							 object_creation_state++;
							 break;
						 case 8:
							 ((Object_Polygon^)(object_list_header->GetNext()))->polygon_size = Convert::ToDouble(textBox7->Text);
							 if(((Object_Polygon^)(object_list_header->GetNext()))->polygon_size == 0) break;
							 ((Object_Polygon^)(object_list_header->GetNext()))->PolygonGenerate(view_x, view_y);
							 object_creation_state++;
							 goto label0;
						 case 10:
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_size = Convert::ToDouble(textBox7->Text);
							 if(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_size == 0) break;
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_y_size = Convert::ToDouble(textBox7->Text);
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ArcLengthUpdate();
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_axis = view_x * Math::Cos(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation) + view_y * Math::Sin(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation);
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_y_axis = view_x * (-Math::Sin(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation)) + view_y * (-Math::Cos(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation));
							 ((Object_Ellipse^)(object_list_header->GetNext()))->Sample(global_scale);
							 object_creation_state++;
						 label0:
							 label5->Text = "Indicate center";
							 textBox7->Text = "0";
							 panelarray[3]->Visible = false;
							 activepanel = 2;
							 panelarray[2]->Visible = true;
							 click_permit = true;
							 break;
						 case 12:
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_size = Convert::ToDouble(textBox7->Text);
							 if(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_size == 0) break;
							 label9->Text = "Indicate minor-axis length";
							 textBox7->Text = "0";
							 object_creation_state++;
							 break;
						 case 13:
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_y_size = Convert::ToDouble(textBox7->Text);
							 if(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_y_size == 0) break;
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ArcLengthUpdate();
							 label9->Text = "Indicate major-axis angle";
							 textBox7->Text = "0";
							 object_creation_state++;
							 break;
						 case 14:
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation = Convert::ToDouble(textBox7->Text);
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_x_axis = view_x * Math::Cos(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation) + view_y * Math::Sin(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation);
							 ((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_y_axis = view_x * (-Math::Sin(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation)) + view_y * (-Math::Cos(((Object_Ellipse^)(object_list_header->GetNext()))->ellipse_rotation));
							 ((Object_Ellipse^)(object_list_header->GetNext()))->Sample(global_scale);
							 object_creation_state++;
							 goto label0;
						 case 28:
							 label9->Text = "Indicate end position x";
							 object_creation_state++;
							 textBox7->Text = "0";							 
							 break;
						 case 29:
							 object_list_header->GetNext()->FinalizeObject();
							 PanelEscape();
							 ((Object_Parabola^)(object_list_header->GetNext()))->Sample(global_scale);
							 Paint(pe);
							 break;
						 case 37:
							 object_list_header->GetNext()->FinalizeObject();
							 PanelEscape();
							 ((Object_BSpline^)(object_list_header->GetNext()))->Sample(global_scale);
							 Paint(pe);
							 break;
						 case 58:
							 label9->Text = "Indicate order in sedond dimension";
							 object_creation_state++;
							 textBox7->Text = Convert::ToString(((Object_BSpline_Surf^)(object_list_header->GetNext()))->order_1);
							 break;
						 case 59:
							 object_list_header->GetNext()->FinalizeObject();
							 PanelEscape();
							 ((Object_BSpline_Surf^)(object_list_header->GetNext()))->Sample(global_scale);
							 Paint(pe);
							 break;
						 case 79:
							 {
								 System::Double temp = Convert::ToDouble(textBox7->Text);
								 if(temp){
									 ((Object_Hyperbola^)(object_list_header->GetNext()))->asymptotic_scale = temp * 25;
									 label9->Text = "Indicate first position y";
									 object_creation_state++;
									 textBox7->Text = "0";
									 break;
								 }
							 }
						 case 80:
							 label9->Text = "Indicate end position y";
							 object_creation_state++;
							 textBox7->Text = "0";							 
							 break;
						 case 81:
							 object_list_header->GetNext()->FinalizeObject();
							 PanelEscape();
							 ((Object_Hyperbola^)(object_list_header->GetNext()))->Sample(global_scale);
							 Paint(pe);						 
							 break;
					 }
				 }
			 }

	private: System::Void circleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	 			 PanelEnter();
				 textBox7->Text = "0";
				 object_list_header->AddObject(gcnew Object_Ellipse(pen_color));
				 label9->Text = "Indicate radius";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 3;
				 panelarray[3]->Visible = true;
				 object_creation_state = 10;
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if(IsCursorInPane()){
					 switch(e->KeyCode){
						 case 0x26: // UP
							 global_shift_y -= 10.0;
							 break;
						 case 0x28: // DOWN
							 global_shift_y += 10.0;
							 break;
						 case 0x25: // LEFT
							 global_shift_x -= 10.0;
							 break;
						 case 0x27: // RIGHT
							 global_shift_x += 10.0;
							 break;
					 }
					 Paint(pe);
				 }
			 }

	private: System::Void ellipseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 		 PanelEnter();
				 textBox7->Text = "0";
				 object_list_header->AddObject(gcnew Object_Ellipse(pen_color));
				 label9->Text = "Indicate major-axis length";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 3;
				 panelarray[3]->Visible = true;
				 object_creation_state = 12;
			 }

	private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(panel_specifier[0] == 1){
					panel_specifier[0] = 2;
					button10->Text = "Bottom";
					panel_controller[0] = 0;
					textBox1->Text = Convert::ToString((brush_color_0<<8)>>24);
					textBox2->Text = Convert::ToString((brush_color_0<<16)>>24);
					textBox3->Text = Convert::ToString((brush_color_0<<24)>>24);
					panel_controller[0] = 1;
				 }
				 else{
					panel_specifier[0] = 1;
					button10->Text = "Top";
					panel_controller[0] = 0;
					textBox1->Text = Convert::ToString((brush_color_1<<8)>>24);
					textBox2->Text = Convert::ToString((brush_color_1<<16)>>24);
					textBox3->Text = Convert::ToString((brush_color_1<<24)>>24);
					panel_controller[0] = 1;
				 }
			 }

	private: System::Void bezierCurveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Bezier_Curve(pen_color));
				 label5->Text = "Indicate start position";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 ((Object_Bezier_Curve^)(object_list_header->GetNext()))->AddVertex(vector3D());
				 object_creation_state = 16;
				 click_permit = true;
			 }

	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEscape();
			 }

	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
				 Panel5Buttons(0);
			 }

	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
				 Panel5Buttons(1);
			 }

	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
				 Panel5Buttons(2);
			 }

	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
				 Panel5Buttons(3);
			 }

	private: System::Void parabolaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 		 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Parabola(pen_color));
				 label5->Text = "Indicate directrix start position";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 object_creation_state = 25;
				 click_permit = true;
			 }

	private: System::Void circularArcToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Ellipse(pen_color));
				 label5->Text = "Indicate first point";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 object_creation_state = 30;
				 click_permit = true;
			 }

	private: System::Void bSplineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 label12->Text = "Indicate curve type";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 5;
				 panelarray[5]->Visible = true;
				 object_creation_state = 33;
			 }

	private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEscape();
			 }

	private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
				 Panel6Buttons();
				 if(object_creation_state == 34) ((Object_BSpline^)(object_list_header->GetNext()))->mode = false;
				 else ((Object_BSpline_Surf^)(object_list_header->GetNext()))->mode = false;
			 }

	private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
				 Panel6Buttons();
				 if(object_creation_state == 34) ((Object_BSpline^)(object_list_header->GetNext()))->mode = true;
				 else ((Object_BSpline_Surf^)(object_list_header->GetNext()))->mode = true;
			 }

	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 ClearAll();
				 InitializeAll();
			 }

	private: System::Void meshToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Mesh(pen_color));
				 label5->Text = "Indicate start position";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 ((Object_Mesh^)(object_list_header->GetNext()))->AddVertex(vector3D());
				 object_creation_state = 38;
				 click_permit = true;
			 }

	private: System::Void bilinearSurfaceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Bilinear_Surf(pen_color));
				 label5->Text = "Indicate 1st corner";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 ((Object_Bilinear_Surf^)(object_list_header->GetNext()))->vertices[0] = gcnew vector3D();
				 object_creation_state = 43;
				 click_permit = true;
			 }

	private: System::Void beziérSurfaceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Bezier_Surf(pen_color));
				 label5->Text = "Indicate start position";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 ((Object_Bezier_Surf^)(object_list_header->GetNext()))->AddVertex(vector3D());
				 object_creation_state = 47;
				 click_permit = true;
			 }

	private: System::Void bSplineSurfaceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter(); 
				 label12->Text = "Indicate surface type";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 5;
				 panelarray[5]->Visible = true;
				 object_creation_state = 52;
			 }

	private: System::Void bicubicSurfaceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Bicubic_Surf(pen_color));
				 label5->Text = "Indicate 1st corner";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 ((Object_Bicubic_Surf^)(object_list_header->GetNext()))->vertices[0] = gcnew vector3D();
				 object_creation_state = 60;
				 click_permit = true;
			 }

	private: System::Void hyperbolaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 		 PanelEnter();
				 object_list_header->AddObject(gcnew Object_Hyperbola(pen_color));
				 label5->Text = "Indicate origin";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 2;
				 panelarray[2]->Visible = true;
				 object_creation_state = 76;
				 click_permit = true;
			 }

	private: System::Void deleteToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_modification_state = 1;
				 selected_object = object_list_header->GetNext();
				 if(selected_object == object_list_header){
					 object_modification_state = 0;
					 return;
				 }
				 selected_object->selected = true;
				 label13->Text = "Indicate the object to delete";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 6;
				 panelarray[6]->Visible = true;
				 Paint(pe);
			 }

	private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEscape();
			 }

	private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
				 switch(object_modification_state){
				 case 1:
					 delete selected_object;
					 PanelEscape();
					 break;
				 case 2:
					 button10->Visible = false;
					 object_modification_state++;
					 textBox1->Text = Convert::ToString((selected_object->object_color<<8)>>24);
					 textBox2->Text = Convert::ToString((selected_object->object_color<<16)>>24);
					 textBox3->Text = Convert::ToString((selected_object->object_color<<24)>>24);
					 panelarray[activepanel]->Visible = false;
					 activepanel = 1;
					 panelarray[1]->Visible = true;
					 break;
				 case 4:
					 object_modification_state++;
					 temp_vector_0 = vector3D();
					 label15->Text = "dX=";
					 label16->Text = "dY=";
					 label17->Text = "dZ=";
					 textBox9->Text = "0";
					 textBox10->Text = "0";
					 textBox11->Text = "0";
					 panelarray[activepanel]->Visible = false;
					 activepanel = 7;
					 panelarray[7]->Visible = true;	
					 break;
				 case 6:
					 object_modification_state++;
					 label5->Text = "Indicate scaling origin";
					 panelarray[activepanel]->Visible = false;
					 activepanel = 2;
					 panelarray[2]->Visible = true;
					 click_permit = true;
					 break;
				 case 9:
					 object_modification_state++;
					 label5->Text = "Indicate first point on rotation axis";
					 panelarray[activepanel]->Visible = false;
					 activepanel = 2;
					 panelarray[2]->Visible = true;	
					 click_permit = true;
					 break;
				 }
			 }

	private: System::Void changeColorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_modification_state = 2;
				 selected_object = object_list_header->GetNext();
				 if(selected_object == object_list_header){
					 object_modification_state = 0;
					 return;
				 }
				 selected_object->selected = true;
				 label13->Text = "Indicate the object to change color";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 6;
				 panelarray[6]->Visible = true;
				 Paint(pe);
			 }

	private: System::Void shiftToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_modification_state = 4;
				 selected_object = object_list_header->GetNext();
				 if(selected_object == object_list_header){
					 object_modification_state = 0;
					 return;
				 }
				 selected_object->selected = true;
				 label13->Text = "Indicate the object to shift";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 6;
				 panelarray[6]->Visible = true;
				 Paint(pe);
			 }

	private: System::Void scaleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_modification_state = 6;
				 selected_object = object_list_header->GetNext();
				 if(selected_object == object_list_header){
					 object_modification_state = 0;
					 return;
				 }
				 selected_object->selected = true;
				 label13->Text = "Indicate the object to scale";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 6;
				 panelarray[6]->Visible = true;
				 Paint(pe);
			 }

	private: System::Void rotateToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEnter();
				 object_modification_state = 9;
				 selected_object = object_list_header->GetNext();
				 if(selected_object == object_list_header){
					 object_modification_state = 0;
					 return;
				 }
				 selected_object->selected = true;
				 label13->Text = "Indicate the object to rotate";
				 panelarray[activepanel]->Visible = false;
				 activepanel = 6;
				 panelarray[6]->Visible = true;
				 Paint(pe);
			 }

	private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) {
				 PanelEscape();
			 }

	private: System::Void textBox9_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(object_modification_state == 5){
					 System::Double shift_x;
					 try{
						 shift_x = Convert::ToDouble(textBox9->Text);
					 }
					 catch (System::FormatException^){
						 textBox9->Text = "0";
						 shift_x = 0;
					 }
					 catch (System::OverflowException^){
						 textBox9->Text = "0";
						 shift_x = 0;
					 }
					 shift_x -= temp_vector_0.p[0];
					 temp_vector_0.p[0] += shift_x;
					 selected_object->Shift(vector3D(shift_x, 0, 0), global_scale);
					 Paint(pe);
				 }
				 else{
					 System::Double scale_x;
					 try{
						 scale_x = Convert::ToDouble(textBox9->Text);
						 if(!scale_x){
							 textBox9->Text = "1";
							 scale_x = 1;
						 }
					 }
					 catch (System::FormatException^){
						 textBox9->Text = "1";
						 scale_x = 1;
					 }
					 catch (System::OverflowException^){
						 textBox9->Text = "1";
						 scale_x = 1;
					 }
					 scale_x /= temp_vector_1.p[0];
					 temp_vector_1.p[0] *= scale_x;
					 selected_object->Scale(temp_vector_0, vector3D(scale_x, 1, 1), global_scale);
					 Paint(pe);
				 }
			 }

	private: System::Void textBox10_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(object_modification_state == 5){
					 System::Double shift_y;
					 try{
						 shift_y = Convert::ToDouble(textBox10->Text);
					 }
					 catch (System::FormatException^){
						 textBox10->Text = "0";
						 shift_y = 0;
					 }
					 catch (System::OverflowException^){
						 textBox10->Text = "0";
						 shift_y = 0;
					 }
					 shift_y -= temp_vector_0.p[1];
					 temp_vector_0.p[1] += shift_y;
					 selected_object->Shift(vector3D(0, shift_y, 0), global_scale);
					 Paint(pe);
				 }
				 else{
					 System::Double scale_y;
					 try{
						 scale_y = Convert::ToDouble(textBox10->Text);
						 if(!scale_y){
							 textBox10->Text = "1";
							 scale_y = 1;
						 }
					 }
					 catch (System::FormatException^){
						 textBox10->Text = "1";
						 scale_y = 1;
					 }
					 catch (System::OverflowException^){
						 textBox10->Text = "1";
						 scale_y = 1;
					 }
					 scale_y /= temp_vector_1.p[1];
					 temp_vector_1.p[1] *= scale_y;
					 selected_object->Scale(temp_vector_0, vector3D(1, scale_y, 1), global_scale);
					 Paint(pe);
				 }
			 }

	private: System::Void textBox11_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(object_modification_state == 5){
					 System::Double shift_z;
					 try{
						 shift_z = Convert::ToDouble(textBox11->Text);
					 }
					 catch (System::FormatException^){
						 textBox11->Text = "0";
						 shift_z = 0;
					 }
					 catch (System::OverflowException^){
						 textBox11->Text = "0";
						 shift_z = 0;
					 }
					 shift_z -= temp_vector_0.p[2];
					 temp_vector_0.p[2] += shift_z;
					 selected_object->Shift(vector3D(0, 0, shift_z), global_scale);
					 Paint(pe);
				 }
				 else{
					 System::Double scale_z;
					 try{
						 scale_z = Convert::ToDouble(textBox11->Text);
						 if(!scale_z){
							 textBox11->Text = "1";
							 scale_z = 1;
						 }
					 }
					 catch (System::FormatException^){
						 textBox11->Text = "1";
						 scale_z = 1;
					 }
					 catch (System::OverflowException^){
						 textBox11->Text = "1";
						 scale_z = 1;
					 }
					 scale_z /= temp_vector_1.p[2];
					 temp_vector_1.p[2] *= scale_z;
					 selected_object->Scale(temp_vector_0, vector3D(1, 1, scale_z), global_scale);
					 Paint(pe);
				 }
			 }
	};
}
