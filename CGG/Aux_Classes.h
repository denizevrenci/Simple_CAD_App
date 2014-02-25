// class definitions
namespace CGG {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	ref class vector3D{
	public:
		//Variables
		array<System::Double>^ p;
		//Constructors
		vector3D(void);
		vector3D(const vector3D% ref_v);
		vector3D(const System::Double& x_c, const System::Double& y_c, const System::Double& z_c);
		//Methods
		void Scale(const vector3D% vector_scale_factor);
		void Scale(const vector3D% scale_origin, const vector3D% vector_scale_factor);
		void Rotate(vector3D rotation_vector, System::Double% theta);
		void Rotate(const vector3D% r_v_start, vector3D r_v_end, System::Double% theta);
		void Unit(void);
		System::Double Magnitude(void);
		System::Double MagnitudeSq(void);
		vector3D XProduct(const vector3D% ref_v);
		System::Double DotProduct(const vector3D% ref_v);
		System::Double Angle_Between(vector3D% ref_v);
		vector3D operator=(const vector3D% ref_v);
		System::Boolean operator==(const vector3D% ref_v);		
		vector3D operator*(const System::Double scalar);
		void operator*=(const System::Double& scalar);
		vector3D operator/(const System::Double& scalar);
		void operator/=(const System::Double& scalar);
		vector3D operator+(const vector3D% addend);
		void operator+=(const vector3D% addend); //also used for translation purposes
		vector3D operator-(const vector3D% subtrahend);
		vector3D operator-(void);
		void operator-=(const vector3D% subtrahend);
	protected:
		//Destructor
		~vector3D(void);
	};

	ref class Screen_Object{
		//Variables
		Screen_Object^ next_object;
		Screen_Object^ prev_object;
		System::Byte object_type_id; //line: 0, polyline: 1, polygon: 2, ellipse: 3, parabola: 4, hyperbola: 5, cubicspline: 6, bezier: 7, b-spline: 8, mesh: 9, bilinearsurf: 10, beziersurf: 11, bsplinesurf: 12, bicubicsurf: 13
		System::Boolean finalized;
	public:
		//Variables
		System::Boolean selected;
		System::UInt32 object_color;	
		//Constructors
		Screen_Object(System::UInt32 color_arg, System::Byte id);
		//Methods
		void FinalizeObject(void);
		System::Boolean IsFinalized(void);
		System::Byte GetObjTypeId(void);
		void SetNext(Screen_Object^ next);
		Screen_Object^ GetNext(void);
		Screen_Object^ GetPrev(void);
		void AddObject(Screen_Object^ s_obj);
		Screen_Object^ DeleteObject(void);
		void Shift(vector3D% shift_vector, System::Double% scale);
		void Scale(vector3D% scale_origin, vector3D% scale_vector, System::Double% scale);
		void Rotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta, System::Double% scale); 
		~Screen_Object(void);
	};

	ref class Object_Line : public Screen_Object{
	public:
		//Variables
		vector3D line_start;
		vector3D line_end;
		//Methods
		void LineShift(vector3D% shift_vector);
		void LineScale(vector3D% scale_origin, vector3D% scale_vector);
		void LineRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta); 
		//Constructor
		Object_Line(System::UInt32% color_arg);
	};

	ref class Object_PolyLine : public Screen_Object{
		void Construct();
	public:
		//Variables
		System::UInt32 current_position;
		System::UInt32 vertex_array_length;
		System::UInt32 vertex_array_max_length;
		array<vector3D^>^ vertices;
		//Constructors
		Object_PolyLine(System::UInt32% color_arg);
		Object_PolyLine(System::UInt32% color_arg, System::Byte id); //used in inheriting classes
		//Methods
		void AddVertex(vector3D% new_vertex);
		void PLShift(vector3D% shift_vector);
		void PLScale(vector3D% scale_origin, vector3D% scale_vector);
		void PLRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta);
		void ClearExtraSpace(void);
	protected:
		//Destructor
		~Object_PolyLine(void);
	};

	ref class Object_Polygon : public Screen_Object{
	public:
		//Variables
		System::UInt32 current_position;
		System::UInt32 vertex_array_length; //number of sides
		vector3D polygon_center;
		System::Double polygon_size;
		System::Double polygon_rotation;
		array<vector3D^>^ vertices;
		//Constructor
		Object_Polygon(System::UInt32% color_arg);
		//Methods
		void PolygonGenerate(vector3D% x_axis, vector3D% y_axis);
		void PolygonShift(vector3D% shift_vector);
		void PolygonScale(vector3D% scale_origin, vector3D% scale_vector);
		void PolygonRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta);
	protected:
		//Destructor
		~Object_Polygon(void);
	};

	ref class Sampled_Object : public Screen_Object{
	public:
		//Variables
		System::UInt32 s_current_position;
		System::UInt32 s_vertex_array_length;
		array<vector3D^>^ sampled_vertices;
		//Constructor
		Sampled_Object(System::UInt32% color_arg, System::Byte id);
		//Methods
		void FlushSamples(void);
	protected:
		//Destructor
		~Sampled_Object(void);
	};

	ref class Sampled_Object_PL_Based : public Object_PolyLine{
	public:
		//Variables
		System::UInt32 s_current_position;
		System::UInt32 s_vertex_array_length;
		array<vector3D^>^ sampled_vertices;
		//Constructor
		Sampled_Object_PL_Based(System::UInt32% color_arg, System::Byte id);
		//Methods
		void FlushSamples(void);
	protected:
		//Destructor
		~Sampled_Object_PL_Based(void);
	};

	ref class Object_Ellipse : public Sampled_Object{
	public:
		//Variables
		vector3D ellipse_center;
		vector3D ellipse_x_axis;
		vector3D ellipse_y_axis;
		System::Double arc_length;
		System::Double ellipse_x_size;
		System::Double ellipse_y_size;
		System::Double ellipse_rotation;
		System::Double angle_difference;
		//Constructor
		Object_Ellipse(System::UInt32% color_arg);
		//Methods
		void Sample(System::Double% scale);
		void EllipseShift(vector3D% shift_vector);
		void EllipseScale(vector3D% scale_origin, vector3D% scale_vector);
		void EllipseRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta);
		void ArcLengthUpdate(void);
	protected:
		//Destructor
		~Object_Ellipse(void);
	};

	ref class Object_Parabola : public Sampled_Object{
	public:
		//Variables
		vector3D parabola_origin;
		vector3D parabola_x_axis;
		vector3D parabola_y_axis;
		System::Double arc_length;
		System::Double parabola_xy_ratio;
		System::Double start_x;
		System::Double x_difference;
		//Constructor
		Object_Parabola(System::UInt32% color_arg);
		//Methods
		void Sample(System::Double% scale);
		void ParabolaShift(vector3D% shift_vector);
		void ParabolaScale(vector3D% scale_origin, vector3D% scale_vector);
		void ParabolaRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta);
		void ArcLengthUpdate(void);
	protected:
		//Destructor
		~Object_Parabola(void);
	};

	ref class Object_Hyperbola : public Sampled_Object{
	public:
		//Variables
		vector3D hyperbola_origin;
		vector3D hyperbola_x_axis;
		vector3D hyperbola_y_axis;
		System::Double arc_length;
		System::Double hyperbola_xy_ratio;
		System::Double asymptotic_scale;
		System::Double start_theta;
		System::Double theta_difference;
		//Constructor
		Object_Hyperbola(System::UInt32% color_arg);
		//Methods
		void Sample(System::Double% scale);
		void HyperbolaShift(vector3D% shift_vector);
		void HyperbolaScale(vector3D% scale_origin, vector3D% scale_vector);
		void HyperbolaRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta);
		void ArcLengthUpdate(void);
	protected:
		//Destructor
		~Object_Hyperbola(void);
	};

	ref class Object_Cubic_Spline : public Sampled_Object_PL_Based{
	public:
		//Variables
		System::Byte end_condition_mode; // 0: clamped, 1: natural, 2: cyclic, 3: anti-cyclic
		vector3D start_derivative;
		vector3D end_derivative;
		array<vector3D^, 2>^ coefficients; // (n-1)x5 array that stores the 4 coefficients and the end point derivative of each segment of the spline.
		//Constructor
		Object_Cubic_Spline(System::UInt32% color_arg);		
		//Methods
		void FlushCoefficients(System::Byte sub);
		void CalculateCoefficients(void);
		void Sample(System::Double% scale);
		void CubicScale(vector3D% scale_vector);
		void CubicRotate(vector3D% rotation_vector, System::Double% theta);
	protected:
		//Destructor
		~Object_Cubic_Spline(void);
	};

	ref class Object_Bezier_Curve : public Sampled_Object_PL_Based{
	public:
		//Variables
		System::Double polygon_length;
		//Constructor
		Object_Bezier_Curve(System::UInt32% color_arg);		
		//Methods
		void Sample(System::Double% scale);
		void PolygonLengthUpdate(void);
	protected:
		//Destructor
		~Object_Bezier_Curve(void);
	};

	ref class Object_BSpline : public Sampled_Object_PL_Based{
	public:
		//Variables
		System::UInt32 s_vertex_array_length;
		System::UInt32* knot;
		System::UInt32 order;
		System::Double polygon_length;
		System::Double** bspline_basis;
		System::Boolean mode; //0: uniform, 1: open uniform
		//Constructor
		Object_BSpline(System::UInt32% color_arg);		
		//Methods
		void Sample(System::Double% scale);
		void BSplineAddVertex(vector3D% new_vertex);
		void KnotUpdate(void);
		void PolygonLengthUpdate(void);
		void BSplineBasis(System::Double% param);
	protected:
		//Destructor
		~Object_BSpline(void);
	};

	ref class Object_Mesh : public Screen_Object{
		void Construct();
	public:
		//Variables
		System::UInt32 current_position_0;
		System::UInt32 current_position_1;
		System::UInt32 vertex_array_length_0;
		System::UInt32 vertex_array_length_1;
		System::UInt32 vertex_array_max_length_0;
		System::UInt32 vertex_array_max_length_1;
		System::Boolean vertex_mode;
		array<vector3D^, 2>^ vertices;
		//Constructors
		Object_Mesh(System::UInt32% color_arg);
		Object_Mesh(System::UInt32% color_arg, System::Byte id); //used in inheriting classes
		//Methods
		void AddVertex(vector3D% new_vertex);
		void MeshShift(vector3D% shift_vector);
		void MeshScale(vector3D% scale_origin, vector3D% scale_vector);
		void MeshRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta);
		void ClearExtraSpace(void);
	protected:
		//Destructor
		~Object_Mesh(void);
	};

	ref class Sampled_Object_Surf : public Screen_Object{
	public:
		//Variables
		System::UInt32 s_current_position_00;
		System::UInt32 s_current_position_01;
		System::UInt32 s_current_position_10;
		System::UInt32 s_current_position_11;
		System::UInt32 s_vertex_array_length_00;
		System::UInt32 s_vertex_array_length_01;
		System::UInt32 s_vertex_array_length_10;
		System::UInt32 s_vertex_array_length_11;
		array<vector3D^, 2>^ sampled_vertices_0;
		array<vector3D^, 2>^ sampled_vertices_1;
		//Constructor
		Sampled_Object_Surf(System::UInt32% color_arg, System::Byte id);
		//Methods
		void FlushSamples(void);
	protected:
		//Destructor
		~Sampled_Object_Surf(void);
	};

	ref class Sampled_Object_Mesh_Based : public Object_Mesh{
	public:
		//Variables
		System::UInt32 a_current_position_0;
		System::UInt32 a_current_position_1;
		System::UInt32 s_current_position_00;
		System::UInt32 s_current_position_01;
		System::UInt32 s_current_position_10;
		System::UInt32 s_current_position_11;
		System::UInt32 s_vertex_array_length_00;
		System::UInt32 s_vertex_array_length_01;
		System::UInt32 s_vertex_array_length_10;
		System::UInt32 s_vertex_array_length_11;
		array<vector3D^, 2>^ sampled_vertices_0;
		array<vector3D^, 2>^ sampled_vertices_1;
		//Constructor
		Sampled_Object_Mesh_Based(System::UInt32% color_arg, System::Byte id);
		//Methods
		void FlushSamples(void);
	protected:
		//Destructor
		~Sampled_Object_Mesh_Based(void);
	};

	ref class Object_Bilinear_Surf : public Sampled_Object_Surf{
	public:
		//Variables
		System::Double polygon_length_0;
		System::Double polygon_length_1;
		array<vector3D^>^ vertices;
		//Constructor
		Object_Bilinear_Surf(System::UInt32% color_arg);		
		//Methods
		void Sample(System::Double% scale);
		void BilinearShift(vector3D% shift_vector);
		void BilinearScale(vector3D% scale_origin, vector3D% scale_vector);
		void BilinearRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta);
		void PolygonLengthUpdate(void);
	protected:
		//Destructor
		~Object_Bilinear_Surf(void);
	};

	ref class Object_Bicubic_Surf : public Sampled_Object_Surf{
	public:
		//Variables
		System::Double polygon_length_0;
		System::Double polygon_length_1;
		array<vector3D^>^ vertices;
		//Constructor
		Object_Bicubic_Surf(System::UInt32% color_arg);		
		//Methods
		void Sample(System::Double% scale);
		void BicubicShift(vector3D% shift_vector);
		void BicubicScale(vector3D% scale_origin, vector3D% scale_vector);
		void BicubicRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta);
		void PolygonLengthUpdate(void);
		System::Double F1(System::Double% param);
		System::Double F2(System::Double% param);
		System::Double F3(System::Double% param);
		System::Double F4(System::Double% param);
	protected:
		//Destructor
		~Object_Bicubic_Surf(void);
	};

	ref class Object_Bezier_Surf : public Sampled_Object_Mesh_Based{
	public:
		//Variables
		System::Double max_polygon_length_0;
		System::Double max_polygon_length_1;
		//Constructor
		Object_Bezier_Surf(System::UInt32% color_arg);		
		//Methods
		void Sample(System::Double% scale);
		void PolygonLengthUpdate(void);
	protected:
		//Destructor
		~Object_Bezier_Surf(void);
	};

	ref class Object_BSpline_Surf : public Sampled_Object_Mesh_Based{
	public:
		//Variables
		System::UInt32* knot_0;
		System::UInt32* knot_1;
		System::UInt32 order_0;
		System::UInt32 order_1;
		System::Double max_polygon_length_0;
		System::Double max_polygon_length_1;
		System::Double** bspline_basis_0;
		System::Double** bspline_basis_1;
		System::Boolean mode; //0: uniform, 1: open uniform
		//Constructor
		Object_BSpline_Surf(System::UInt32% color_arg);		
		//Methods
		void Sample(System::Double% scale);
		void BSplineAddVertex(vector3D% new_vertex);
		void KnotUpdate0(void);
		void KnotUpdate1(void);
		void PolygonLengthUpdate(void);
		void BSplineBasis0(System::Double% param, System::Boolean% end);
		void BSplineBasis1(System::Double% param, System::Boolean% end);
	protected:
		//Destructor
		~Object_BSpline_Surf(void);
	};
}
