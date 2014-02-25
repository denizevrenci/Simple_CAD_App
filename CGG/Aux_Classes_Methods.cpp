#include <stdafx.h>

namespace CGG {

	/******************************************************************
	********************Methods of vector3D class**********************
	*******************************************************************/

	vector3D::vector3D(void){
		p = gcnew array<System::Double> {0, 0, 0};
	}

	vector3D::vector3D(const vector3D% ref_v){
		p = gcnew array<System::Double> {ref_v.p[0], ref_v.p[1], ref_v.p[2]};
	}

	vector3D::vector3D(const System::Double& x_c, const System::Double& y_c, const System::Double& z_c){
		p = gcnew array<System::Double> {x_c, y_c, z_c};
	}

	void vector3D::Scale(const vector3D% vector_scale_factor){
		p[0] = vector_scale_factor.p[0] * p[0];
		p[1] = vector_scale_factor.p[1] * p[1];
		p[2] = vector_scale_factor.p[2] * p[2];
	}

	void vector3D::Scale(const vector3D% scale_origin, const vector3D% vector_scale_factor){
		*this -= scale_origin;
		p[0] = vector_scale_factor.p[0] * p[0];
		p[1] = vector_scale_factor.p[1] * p[1];
		p[2] = vector_scale_factor.p[2] * p[2];
		*this += scale_origin;
	}

	void vector3D::Rotate(vector3D rotation_vector, System::Double% theta){
		rotation_vector.Unit();
		System::Double cos_theta = Math::Cos(theta);
		System::Double sin_theta = Math::Sin(theta);
		System::Double temp_0, temp_1;
		temp_0 = p[0] * (rotation_vector.p[0] * rotation_vector.p[0] + (1.0 - Math::Pow(rotation_vector.p[0], 2.0)) * cos_theta)
			+ p[1] * (rotation_vector.p[0] * rotation_vector.p[1] * (1.0 - cos_theta) - rotation_vector.p[2] * sin_theta)
			+ p[2] * (rotation_vector.p[0] * rotation_vector.p[2] * (1.0 - cos_theta) + rotation_vector.p[1] * sin_theta);
		temp_1 = p[0] * (rotation_vector.p[0] * rotation_vector.p[1] * (1.0 - cos_theta) + rotation_vector.p[2] * sin_theta)
			+ p[1] * (rotation_vector.p[1] * rotation_vector.p[1] + (1.0 - Math::Pow(rotation_vector.p[1], 2.0)) * cos_theta)
			+ p[2] * (rotation_vector.p[1] * rotation_vector.p[2] * (1.0 - cos_theta) - rotation_vector.p[0] * sin_theta);
		p[2] = p[0] * (rotation_vector.p[0] * rotation_vector.p[2] * (1.0 - cos_theta) - rotation_vector.p[1] * sin_theta)
			+ p[1] * (rotation_vector.p[1] * rotation_vector.p[2] * (1.0 - cos_theta) + rotation_vector.p[0] * sin_theta)
			+ p[2] * (rotation_vector.p[2] * rotation_vector.p[2] + (1.0 - Math::Pow(rotation_vector.p[2], 2.0)) * cos_theta);
		p[0] = temp_0;
		p[1] = temp_1;
	}

	void vector3D::Rotate(const vector3D% r_v_start, vector3D r_v_end, System::Double% theta){
		*this -= r_v_start;
		r_v_end -= r_v_start;
		vector3D::Rotate(r_v_end, theta);
		*this += r_v_start;
	}

	void vector3D::Unit(void){
		System::Double mag = Magnitude();
		if(!mag) return;
		*this /= mag;
	}

	System::Double vector3D::Magnitude(void){
		return Math::Sqrt(Math::Pow(p[0], 2.0) + Math::Pow(p[1], 2.0) + Math::Pow(p[2], 2.0));
	}

	System::Double vector3D::MagnitudeSq(void){
		return (Math::Pow(p[0], 2.0) + Math::Pow(p[1], 2.0) + Math::Pow(p[2], 2.0));
	}

	vector3D vector3D::XProduct(const vector3D% ref_v){
		return vector3D((p[1] * ref_v.p[2] - p[2] * ref_v.p[1]),
			(p[2] * ref_v.p[0] - p[0] * ref_v.p[2]),
			(p[0] * ref_v.p[1] - p[1] * ref_v.p[0]));
	}

	System::Double vector3D::DotProduct(const vector3D% ref_v){
		return (p[0] * ref_v.p[0] + p[1] * ref_v.p[1] + p[2] * ref_v.p[2]);
	}

	System::Double vector3D::Angle_Between(vector3D% ref_v){
		return Math::Acos(DotProduct(ref_v) / (Magnitude() * ref_v.Magnitude()));
	}

	vector3D vector3D::operator=(const vector3D% ref_v){
		p[0] = ref_v.p[0];
		p[1] = ref_v.p[1];
		p[2] = ref_v.p[2];
		return *this;
	}

	System::Boolean vector3D::operator==(const vector3D% ref_v){
		if((ref_v.p[0] == p[0]) && (ref_v.p[1] == p[1]) && (ref_v.p[2] == p[2])) return true;
		return false;
	}

	vector3D vector3D::operator*(const System::Double scalar){
		return vector3D((p[0] * scalar), (p[1] * scalar), (p[2] * scalar));
	}

	void vector3D::operator*=(const System::Double& scalar){
		*this = *this * scalar;
	}

	vector3D vector3D::operator/(const System::Double& scalar){
		return (*this * (1 / scalar));
	}

	void vector3D::operator/=(const System::Double& scalar){
		*this = *this / scalar;
	}

	vector3D vector3D::operator+(const vector3D% addend){
		return vector3D((p[0] + addend.p[0]), (p[1] + addend.p[1]), (p[2] + addend.p[2]));
	}

	void vector3D::operator+=(const vector3D% addend){
		*this = *this + addend;
	}

	vector3D vector3D::operator-(const vector3D% subtrahend){
		return vector3D((p[0] - subtrahend.p[0]), (p[1] - subtrahend.p[1]), (p[2] - subtrahend.p[2]));
	}

	vector3D vector3D::operator-(void){
		return vector3D(-p[0], -p[1], -p[2]);
	}

	void vector3D::operator-=(const vector3D% subtrahend){
		*this = *this - subtrahend;
	}

	vector3D::~vector3D(void){
		delete p;
	}

	/******************************************************************
	******************Methods of Screen_Object class*******************
	*******************************************************************/

	Screen_Object::Screen_Object(System::UInt32 color_arg, System::Byte id){
		finalized = false;
		selected = true;
		object_color = color_arg;
		object_type_id = id;
		next_object = this;
		prev_object = this;
	}

	void Screen_Object::FinalizeObject(void){
		finalized = true;
		selected = false;
	}

	System::Boolean Screen_Object::IsFinalized(void){
		return finalized;
	}

	System::Byte Screen_Object::GetObjTypeId(void){
		return object_type_id;
	}

	void Screen_Object::SetNext(Screen_Object^ next){
		next_object = next;
	}

	Screen_Object^ Screen_Object::GetNext(void){
		return next_object;
	}

	Screen_Object^ Screen_Object::GetPrev(void){
		return prev_object;
	}

	void Screen_Object::AddObject(Screen_Object^ s_obj){
		Screen_Object^ temp = next_object;
		next_object = s_obj;
		next_object->next_object = temp;
		next_object->prev_object = this;
		temp->prev_object = next_object;
	}

	Screen_Object^ Screen_Object::DeleteObject(void){
		Screen_Object^ temp = next_object;
		next_object = next_object->next_object;
		next_object->prev_object = this;
		return temp;
	}

	void Screen_Object::Shift(vector3D% shift_vector, System::Double% scale){
		switch(object_type_id){
		case 0:
			((Object_Line^)this)->LineShift(shift_vector);
			break;
		case 1:
			((Object_PolyLine^)this)->PLShift(shift_vector);
			break;
		case 2:
			((Object_Polygon^)this)->PolygonShift(shift_vector);
			break;
		case 3:
			((Object_Ellipse^)this)->EllipseShift(shift_vector);
			((Object_Ellipse^)this)->Sample(scale);
			break;
		case 4:
			((Object_Parabola^)this)->ParabolaShift(shift_vector);
			((Object_Parabola^)this)->Sample(scale);
			break;
		case 5:
			((Object_Hyperbola^)this)->HyperbolaShift(shift_vector);
			((Object_Hyperbola^)this)->Sample(scale);
			break;
		case 6:
			((Object_Cubic_Spline^)this)->PLShift(shift_vector);
			((Object_Cubic_Spline^)this)->CalculateCoefficients();
			((Object_Cubic_Spline^)this)->Sample(scale);
			break;
		case 7:
			((Object_Bezier_Curve^)this)->PLShift(shift_vector);
			((Object_Bezier_Curve^)this)->Sample(scale);
			break;
		case 8:
			((Object_BSpline^)this)->PLShift(shift_vector);
			((Object_BSpline^)this)->Sample(scale);
			break;
		case 9:
			((Object_Mesh^)this)->MeshShift(shift_vector);
			break;
		case 10:
			((Object_Bilinear_Surf^)this)->BilinearShift(shift_vector);
			((Object_Bilinear_Surf^)this)->Sample(scale);
			break;
		case 11:
			((Object_Bezier_Surf^)this)->MeshShift(shift_vector);
			((Object_Bezier_Surf^)this)->Sample(scale);
			break;
		case 12:
			((Object_BSpline_Surf^)this)->MeshShift(shift_vector);
			((Object_BSpline_Surf^)this)->Sample(scale);
			break;
		case 13:
			((Object_Bicubic_Surf^)this)->BicubicShift(shift_vector);
			((Object_Bicubic_Surf^)this)->Sample(scale);
			break;
		}
	}

	void Screen_Object::Scale(vector3D% scale_origin, vector3D% scale_vector, System::Double% scale){
		switch(object_type_id){
		case 0:
			((Object_Line^)this)->LineScale(scale_origin, scale_vector);
			break;
		case 1:
			((Object_PolyLine^)this)->PLScale(scale_origin, scale_vector);
			break;
		case 2:
			((Object_Polygon^)this)->PolygonScale(scale_origin, scale_vector);
			break;
		case 3:
			((Object_Ellipse^)this)->EllipseScale(scale_origin, scale_vector);
			((Object_Ellipse^)this)->ArcLengthUpdate();
			((Object_Ellipse^)this)->Sample(scale);
			break;
		case 4:
			((Object_Parabola^)this)->ParabolaScale(scale_origin, scale_vector);
			((Object_Parabola^)this)->ArcLengthUpdate();
			((Object_Parabola^)this)->Sample(scale);
			break;
		case 5:
			((Object_Hyperbola^)this)->HyperbolaScale(scale_origin, scale_vector);
			((Object_Hyperbola^)this)->ArcLengthUpdate();
			((Object_Hyperbola^)this)->Sample(scale);
			break;
		case 6:
			((Object_Cubic_Spline^)this)->PLScale(scale_origin, scale_vector);
			((Object_Cubic_Spline^)this)->CubicScale(scale_vector);
			((Object_Cubic_Spline^)this)->CalculateCoefficients();
			((Object_Cubic_Spline^)this)->Sample(scale);
			break;
		case 7:
			((Object_Bezier_Curve^)this)->PLScale(scale_origin, scale_vector);
			((Object_Bezier_Curve^)this)->PolygonLengthUpdate();
			((Object_Bezier_Curve^)this)->Sample(scale);
			break;
		case 8:
			((Object_BSpline^)this)->PLScale(scale_origin, scale_vector);
			((Object_BSpline^)this)->PolygonLengthUpdate();
			((Object_BSpline^)this)->Sample(scale);
			break;
		case 9:
			((Object_Mesh^)this)->MeshScale(scale_origin, scale_vector);
			break;
		case 10:
			((Object_Bilinear_Surf^)this)->BilinearScale(scale_origin, scale_vector);
			((Object_Bilinear_Surf^)this)->PolygonLengthUpdate();
			((Object_Bilinear_Surf^)this)->Sample(scale);
			break;
		case 11:
			((Object_Bezier_Surf^)this)->MeshScale(scale_origin, scale_vector);
			((Object_Bezier_Surf^)this)->PolygonLengthUpdate();
			((Object_Bezier_Surf^)this)->Sample(scale);
			break;
		case 12:
			((Object_BSpline_Surf^)this)->MeshScale(scale_origin, scale_vector);
			((Object_BSpline_Surf^)this)->PolygonLengthUpdate();
			((Object_BSpline_Surf^)this)->Sample(scale);
			break;
		case 13:
			((Object_Bicubic_Surf^)this)->BicubicScale(scale_origin, scale_vector);
			((Object_Bicubic_Surf^)this)->PolygonLengthUpdate();
			((Object_Bicubic_Surf^)this)->Sample(scale);
			break;
		}
	}

	void Screen_Object::Rotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta, System::Double% scale){
		switch(object_type_id){
		case 0:
			((Object_Line^)this)->LineRotate(r_v_start, r_v_end, theta);
			break;
		case 1:
			((Object_PolyLine^)this)->PLRotate(r_v_start, r_v_end, theta);
			break;
		case 2:
			((Object_Polygon^)this)->PolygonRotate(r_v_start, r_v_end, theta);
			break;
		case 3:
			((Object_Ellipse^)this)->EllipseRotate(r_v_start, r_v_end, theta);
			((Object_Ellipse^)this)->Sample(scale);
			break;
		case 4:
			((Object_Parabola^)this)->ParabolaRotate(r_v_start, r_v_end, theta);
			((Object_Parabola^)this)->Sample(scale);
			break;
		case 5:
			((Object_Hyperbola^)this)->HyperbolaRotate(r_v_start, r_v_end, theta);
			((Object_Hyperbola^)this)->Sample(scale);
			break;
		case 6:
			((Object_Cubic_Spline^)this)->PLRotate(r_v_start, r_v_end, theta);
			((Object_Cubic_Spline^)this)->CubicRotate(r_v_end - r_v_start, theta);
			((Object_Cubic_Spline^)this)->CalculateCoefficients();
			((Object_Cubic_Spline^)this)->Sample(scale);
			break;
		case 7:
			((Object_Bezier_Curve^)this)->PLRotate(r_v_start, r_v_end, theta);
			((Object_Bezier_Curve^)this)->Sample(scale);
			break;
		case 8:
			((Object_BSpline^)this)->PLRotate(r_v_start, r_v_end, theta);
			((Object_BSpline^)this)->Sample(scale);
		case 9:
			((Object_Mesh^)this)->MeshRotate(r_v_start, r_v_end, theta);
			break;
		case 10:
			((Object_Bilinear_Surf^)this)->BilinearRotate(r_v_start, r_v_end, theta);
			((Object_Bilinear_Surf^)this)->Sample(scale);
			break;
		case 11:
			((Object_Bezier_Surf^)this)->MeshRotate(r_v_start, r_v_end, theta);
			((Object_Bezier_Surf^)this)->Sample(scale);
			break;
		case 12:
			((Object_BSpline_Surf^)this)->MeshRotate(r_v_start, r_v_end, theta);
			((Object_BSpline_Surf^)this)->Sample(scale);
			break;
		case 13:
			((Object_Bicubic_Surf^)this)->BicubicRotate(r_v_start, r_v_end, theta);
			((Object_Bicubic_Surf^)this)->Sample(scale);
			break;
		}
	}

	Screen_Object::~Screen_Object(void){
		next_object->prev_object = prev_object;
		prev_object->next_object = next_object;
	}

	/******************************************************************
	*******************Methods of Object_Line class********************
	*******************************************************************/

	Object_Line::Object_Line(System::UInt32% color_arg) : Screen_Object(color_arg, 0){}

	void Object_Line::LineShift(vector3D% shift_vector){
		line_start += shift_vector;
		line_end += shift_vector;
	}

	void Object_Line::LineScale(vector3D% scale_origin, vector3D% scale_vector){
		line_start.Scale(scale_origin, scale_vector);
		line_end.Scale(scale_origin, scale_vector);
	}

	void Object_Line::LineRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		line_start.Rotate(r_v_start, r_v_end, theta);
		line_end.Rotate(r_v_start, r_v_end, theta);
	}

	/******************************************************************
	*****************Methods of Object_Polyline class******************
	*******************************************************************/

	Object_PolyLine::Object_PolyLine(System::UInt32% color_arg) : Screen_Object(color_arg, 1){
		Construct();
	}

	Object_PolyLine::Object_PolyLine(System::UInt32% color_arg, System::Byte id) : Screen_Object(color_arg, id){
		Construct();
	}

	void Object_PolyLine::Construct(){
		current_position = 0;
		vertex_array_length = 0;
		vertex_array_max_length = 4;
		vertices = gcnew array<vector3D^>(4);
	}

	void Object_PolyLine::AddVertex(vector3D% new_vertex){
		if(current_position >= vertex_array_max_length){
			array<vector3D^>^ temporary_array = gcnew array<vector3D^>((vertex_array_max_length += 4));
			for(current_position = 0; current_position < vertex_array_length; current_position++)
				temporary_array[current_position] = vertices[current_position];
			delete []vertices;
			vertices = temporary_array;
		}
		vertices[current_position++] = gcnew vector3D(new_vertex);
		vertex_array_length++;
	}

	void Object_PolyLine::PLShift(vector3D% shift_vector){
		for(current_position = 0; current_position < vertex_array_length; current_position++)
			vertices[current_position] += shift_vector;
	}

	void Object_PolyLine::PLScale(vector3D% scale_origin, vector3D% scale_vector){
		for(current_position = 0; current_position < vertex_array_length; current_position++)
			(vertices[current_position])->Scale(scale_origin, scale_vector);
	}

	void Object_PolyLine::PLRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		for(current_position = 0; current_position < vertex_array_length; current_position++)
			(vertices[current_position])->Rotate(r_v_start, r_v_end, theta);
	}

	void Object_PolyLine::ClearExtraSpace(void){
		if(current_position == vertex_array_max_length) return;
		array<vector3D^>^ temporary_array = gcnew array<vector3D^>(current_position + 1);
		for(vertex_array_length = 0; vertex_array_length <= current_position; vertex_array_length++)
			temporary_array[vertex_array_length] = vertices[vertex_array_length];
		delete []vertices;
		vertices = temporary_array;
	}

	Object_PolyLine::~Object_PolyLine(void){
		for(current_position = 0; current_position < vertex_array_length; current_position++)
			delete vertices[current_position];
		delete []vertices;
	}

	/******************************************************************
	*****************Methods of Object_Polygon class*******************
	*******************************************************************/

	Object_Polygon::Object_Polygon(System::UInt32% color_arg) : Screen_Object(color_arg, 2){}

	void Object_Polygon::PolygonGenerate(vector3D% x_axis, vector3D% y_axis){
		System::Double sampling_angle = polygon_rotation;
		vertices = gcnew array<vector3D^>(vertex_array_length);
		for(current_position = 0; current_position < vertex_array_length; current_position++){
			vertices[current_position] = gcnew vector3D(polygon_center + x_axis * (polygon_size * Math::Cos(sampling_angle)) + y_axis * (polygon_size * Math::Sin(sampling_angle)));
			sampling_angle += PI2 / vertex_array_length;
		}
	}

	void Object_Polygon::PolygonShift(vector3D% shift_vector){
		for(current_position = 0; current_position < vertex_array_length; current_position++)
			vertices[current_position] += shift_vector;
	}

	void Object_Polygon::PolygonScale(vector3D% scale_origin, vector3D% scale_vector){
		for(current_position = 0; current_position < vertex_array_length; current_position++)
			(vertices[current_position])->Scale(scale_origin, scale_vector);
	}

	void Object_Polygon::PolygonRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		for(current_position = 0; current_position < vertex_array_length; current_position++)
			(vertices[current_position])->Rotate(r_v_start, r_v_end, theta);
	}

	Object_Polygon::~Object_Polygon(void){
		for(current_position = 0; current_position < vertex_array_length; current_position++)
			delete vertices[current_position];
		delete []vertices;
	}

	/******************************************************************
	*****************Methods of Sampled_Object class*******************
	*******************************************************************/

	Sampled_Object::Sampled_Object(System::UInt32% color_arg, System::Byte id) : Screen_Object(color_arg, id){
		s_vertex_array_length = 0;
		sampled_vertices = gcnew array<vector3D^>(0);
	}

	void Sampled_Object::FlushSamples(void){
		for(s_current_position = 0; s_current_position < s_vertex_array_length; s_current_position++)
			delete sampled_vertices[s_current_position];
		delete []sampled_vertices;
	}

	Sampled_Object::~Sampled_Object(void){
		FlushSamples();
	}

	/******************************************************************
	*************Methods of Sampled_Object_PL_Based class**************
	*******************************************************************/

	Sampled_Object_PL_Based::Sampled_Object_PL_Based(System::UInt32% color_arg, System::Byte id) : Object_PolyLine(color_arg, id){
		s_vertex_array_length = 0;
		sampled_vertices = gcnew array<vector3D^>(0);
	}

	void Sampled_Object_PL_Based::FlushSamples(void){
		for(s_current_position = 0; s_current_position < s_vertex_array_length; s_current_position++)
			delete sampled_vertices[s_current_position];
		delete []sampled_vertices;
	}

	Sampled_Object_PL_Based::~Sampled_Object_PL_Based(void){
		FlushSamples();
	}

	/******************************************************************
	******************Methods of Object_Ellipse class******************
	*******************************************************************/

	Object_Ellipse::Object_Ellipse(System::UInt32% color_arg) : Sampled_Object(color_arg, 3){
		angle_difference = PI2;
	}

	void Object_Ellipse::Sample(System::Double% scale){
		FlushSamples();
		System::Double sampling_angle = 0;
		if(angle_difference == PI2){
			System::UInt32 quarter = (System::UInt32)(Math::Round(Math::Pow((scale * CIRCLE_SAMPLE * arc_length), SAMPLE_DECAY)));
			s_vertex_array_length = (quarter << 2);
			sampled_vertices = gcnew array<vector3D^>(s_vertex_array_length + 1);		
			for(s_current_position = 0; s_current_position <= quarter; s_current_position++){
				System::Double cos_ang = Math::Cos(sampling_angle);
				System::Double sin_ang = Math::Sin(sampling_angle);
				sampled_vertices[s_current_position] = gcnew vector3D(ellipse_center + (ellipse_x_axis * ellipse_x_size * cos_ang) + (ellipse_y_axis * ellipse_y_size * sin_ang));
				sampled_vertices[(quarter << 1) - s_current_position] = gcnew vector3D(ellipse_center + (ellipse_x_axis * ellipse_x_size * -cos_ang) + (ellipse_y_axis * ellipse_y_size * sin_ang));
				sampled_vertices[(quarter << 1) + s_current_position] = gcnew vector3D(ellipse_center + (ellipse_x_axis * ellipse_x_size * -cos_ang) + (ellipse_y_axis * ellipse_y_size * -sin_ang));
				sampled_vertices[s_vertex_array_length - s_current_position] = gcnew vector3D(ellipse_center + (ellipse_x_axis * ellipse_x_size * cos_ang) + (ellipse_y_axis * ellipse_y_size * -sin_ang));
				sampling_angle += (PI2 / System::Double(s_vertex_array_length));
			}
			s_vertex_array_length++;
		}
		else
		{
			s_vertex_array_length = (System::UInt32)(Math::Round(Math::Pow((scale * CIRCLE_ARC_SAMPLE * arc_length * Math::Abs(angle_difference)), SAMPLE_DECAY)));
			sampled_vertices = gcnew array<vector3D^>(s_vertex_array_length);			
			for(s_current_position = 0; s_current_position < s_vertex_array_length; s_current_position++){
				System::Double cos_ang = Math::Cos(sampling_angle);
				System::Double sin_ang = Math::Sin(sampling_angle);
				sampled_vertices[s_current_position] = gcnew vector3D(ellipse_center + (ellipse_x_axis * ellipse_x_size * cos_ang) + (ellipse_y_axis * ellipse_y_size * sin_ang));
				sampling_angle += (angle_difference / System::Double(s_vertex_array_length - 1));
			}
		}
	}

	void Object_Ellipse::EllipseShift(vector3D% shift_vector){
		ellipse_center += shift_vector;
	}

	void Object_Ellipse::EllipseScale(vector3D% scale_origin, vector3D% scale_vector){
		ellipse_center.Scale(scale_origin, scale_vector);
		ellipse_x_axis.Scale(scale_vector);
		ellipse_y_axis.Scale(scale_vector);
	}

	void Object_Ellipse::EllipseRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		vector3D rotator = r_v_end - r_v_start;
		ellipse_center.Rotate(r_v_start, r_v_end, theta);
		ellipse_x_axis.Rotate(rotator, theta);
		ellipse_y_axis.Rotate(rotator, theta);
	}

	void Object_Ellipse::ArcLengthUpdate(void){
		System::Double x_size = ellipse_x_size * ellipse_x_axis.Magnitude();
		System::Double y_size = ellipse_y_size * ellipse_y_axis.Magnitude();
		arc_length = (3.0 * (x_size + y_size) - Math::Sqrt(10 * x_size * y_size + 3 * (Math::Pow(x_size, 2) + Math::Pow(y_size, 2))));
	}

	Object_Ellipse::~Object_Ellipse(void){}

	/******************************************************************
	*****************Methods of Object_Parabola class******************
	*******************************************************************/

	Object_Parabola::Object_Parabola(System::UInt32% color_arg) : Sampled_Object(color_arg, 4){}

	void Object_Parabola::Sample(System::Double% scale){
		FlushSamples();
		s_vertex_array_length = (System::UInt32)(Math::Round(Math::Pow((scale * arc_length), SAMPLE_DECAY)));
		sampled_vertices = gcnew array<vector3D^>(s_vertex_array_length + 1);
		System::Double sampling_x = start_x;			
		for(s_current_position = 0; s_current_position <= s_vertex_array_length; s_current_position++){
			sampled_vertices[s_current_position] = gcnew vector3D(parabola_origin + (parabola_x_axis * sampling_x) + (parabola_y_axis * (Math::Pow(sampling_x, 2) / parabola_xy_ratio)));
			sampling_x += (x_difference / System::Double(s_vertex_array_length));
		}
		s_vertex_array_length++;
	}

	void Object_Parabola::ParabolaShift(vector3D% shift_vector){
		parabola_origin += shift_vector;
	}

	void Object_Parabola::ParabolaScale(vector3D% scale_origin, vector3D% scale_vector){
		parabola_origin.Scale(scale_origin, scale_vector);
		parabola_x_axis.Scale(scale_vector);
		parabola_y_axis.Scale(scale_vector);
	}

	void Object_Parabola::ParabolaRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		vector3D rotator = r_v_end - r_v_start;
		parabola_origin.Rotate(r_v_start, r_v_end, theta);
		parabola_x_axis.Rotate(rotator, theta);
		parabola_y_axis.Rotate(rotator, theta);
	}

	void Object_Parabola::ArcLengthUpdate(void){
		arc_length = Math::Abs(x_difference) * PARABOLA_SAMPLE * (parabola_xy_ratio + 1) * parabola_x_axis.Magnitude() * parabola_y_axis.Magnitude();
	}

	Object_Parabola::~Object_Parabola(void){}

	/******************************************************************
	****************Methods of Object_Hyperbola class******************
	*******************************************************************/

	Object_Hyperbola::Object_Hyperbola(System::UInt32% color_arg) : Sampled_Object(color_arg, 5){
		asymptotic_scale = 25;
	}

	void Object_Hyperbola::Sample(System::Double% scale){
		FlushSamples();
		s_vertex_array_length = (System::UInt32)(Math::Round(Math::Pow((scale * arc_length), SAMPLE_DECAY)));
		sampled_vertices = gcnew array<vector3D^>(s_vertex_array_length + 1);
		System::Double sampling_theta = start_theta;			
		for(s_current_position = 0; s_current_position <= s_vertex_array_length; s_current_position++){
			sampled_vertices[s_current_position] = gcnew vector3D(hyperbola_origin + (hyperbola_x_axis * Math::Cosh(sampling_theta) * hyperbola_xy_ratio * asymptotic_scale) + (hyperbola_y_axis * Math::Sinh(sampling_theta) * asymptotic_scale));
			sampling_theta += (theta_difference / System::Double(s_vertex_array_length));
		}
		s_vertex_array_length++;
	}

	void Object_Hyperbola::HyperbolaShift(vector3D% shift_vector){
		hyperbola_origin += shift_vector;
	}

	void Object_Hyperbola::HyperbolaScale(vector3D% scale_origin, vector3D% scale_vector){
		hyperbola_origin.Scale(scale_origin, scale_vector);
		hyperbola_x_axis.Scale(scale_vector);
		hyperbola_y_axis.Scale(scale_vector);	
	}

	void Object_Hyperbola::HyperbolaRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		vector3D rotator = r_v_end - r_v_start;
		hyperbola_origin.Rotate(r_v_start, r_v_end, theta);
		hyperbola_x_axis.Rotate(rotator, theta);
		hyperbola_y_axis.Rotate(rotator, theta);
	}

	void Object_Hyperbola::ArcLengthUpdate(void){
		arc_length = Math::Sinh(Math::Abs(theta_difference)) * HYPERBOLA_SAMPLE * (hyperbola_xy_ratio + 1) * hyperbola_x_axis.Magnitude() * hyperbola_y_axis.Magnitude();
	}

	Object_Hyperbola::~Object_Hyperbola(void){}

	/******************************************************************
	****************Methods of Object_Cubic_Spline class***************
	*******************************************************************/

	Object_Cubic_Spline::Object_Cubic_Spline(System::UInt32% color_arg) : Sampled_Object_PL_Based(color_arg, 6){
		coefficients = gcnew array<vector3D^, 2>(1, 5);
	}

	void Object_Cubic_Spline::FlushCoefficients(System::Byte sub){
		System::Byte cnt;
		for(current_position = 0; current_position < ((System::Int64)vertex_array_length - (sub + 1)); current_position++)
			for(cnt = 0; cnt < 5; cnt++)
				delete coefficients[current_position, cnt];
		delete []coefficients;
	}

	void Object_Cubic_Spline::CalculateCoefficients(void){
		System::Double id;
		System::Boolean end_cond = false;
		System::Double* a = new System::Double[vertex_array_length];
		System::Double* b = new System::Double[vertex_array_length];
		System::Double* c = new System::Double[vertex_array_length];
		System::Double* c1 = new System::Double[vertex_array_length];
		array<vector3D^>^ d = gcnew array<vector3D^>(vertex_array_length);
		array<vector3D^>^ d1 = gcnew array<vector3D^>(vertex_array_length);
		array<vector3D^>^ x = gcnew array<vector3D^>(vertex_array_length);
		for(current_position = 0; current_position < vertex_array_length; current_position++){
			d[current_position] = gcnew vector3D();
			d1[current_position] = gcnew vector3D();
			x[current_position] = gcnew vector3D();
		}
		for(current_position = 0; current_position < vertex_array_length; current_position++){
			a[current_position] = c[current_position] = 1;
			b[current_position] = 4;
			if(current_position < ((System::Int64)(vertex_array_length) - 2)) *d[current_position + 1] = (*vertices[current_position + 2] - *vertices[current_position]) * 3;
		}
		switch (end_condition_mode){
		case 0:
			b[0] = b[vertex_array_length - 1] = 1;
			c[0] = 0;
			a[vertex_array_length - 1] = 0;
			*d[0] = start_derivative;
			*d[vertex_array_length - 1] = end_derivative;
			break;
		case 1:
			b[0] = 1;
			c[0] = 0.5;
			a[vertex_array_length - 1] = 2;
			*d[0] = (*vertices[1] - *vertices[0]) * 1.5;
			*d[vertex_array_length - 1] = (*vertices[vertex_array_length - 1] - *vertices[vertex_array_length - 2]) * 6;
			break;
		case 2:
			*d[0] = (*vertices[1] - *vertices[0] + *vertices[vertex_array_length - 1] - *vertices[vertex_array_length - 2]) * 3;
			vertex_array_length--;
			end_cond = true;
			break;
		case 3:
			*d[0] = (*vertices[1] - *vertices[0] - *vertices[vertex_array_length - 1] + *vertices[vertex_array_length - 2]) * 3;
			vertex_array_length--;
			end_cond = true;
			break;
		}
		// Tridiagonal matrix solution - Start
		// Modify the coefficients.
		c1[0] = c[0] / b[0];
		*d1[0] = d[0] / b[0];
		for (current_position = 1; current_position < vertex_array_length; current_position++){
			id = 1 / (b[current_position] - c1[current_position-1] * a[current_position]);  // Division by zero risk.
			c1[current_position] = c[current_position] * id; // Last value calculated is redundant.
			*d1[current_position] = (*d[current_position] - *d1[current_position - 1] * a[current_position]) * id;
		}		 
		// Now back substitute.
		*x[vertex_array_length - 1] = *d1[vertex_array_length - 1];
		if(end_cond && (vertex_array_length == 1));
		else
			for (current_position = (vertex_array_length - 2); current_position > 0; current_position--)
				*x[current_position] = *d1[current_position] - *x[current_position + 1] * c1[current_position];
		*x[0] = *d1[0] - *x[1] * c1[0];
		//Tridiagonal matrix solution - End
		if(end_cond){
			// Tridiagonal matrix solution for correction - Start
			c1[0] = c[0] / b[0];
			*d1[0] = vector3D(1, 1, 1) / b[0];
			for (current_position = 1; current_position < vertex_array_length; current_position++){
				id = 1 / (b[current_position] - c[current_position-1] * a[current_position]);  // Division by zero risk.
				c1[current_position] = c[current_position] * id; // Last value calculated is redundant.
				*d1[current_position] = -(*d1[current_position - 1] * a[current_position]) * id;
			}		 
			// Now back substitute.
			array<vector3D^>^ x1 = gcnew array<vector3D^>(vertex_array_length + 1);
			for(current_position = 0; current_position < (vertex_array_length + 1); current_position++){
				x1[current_position] = gcnew vector3D();
			}
			*x1[vertex_array_length - 1] = *d1[vertex_array_length - 1];
			if(vertex_array_length == 1);
			else
				for (current_position = (vertex_array_length - 2); current_position > 0; current_position--)
					*x1[current_position] = *d1[current_position] - *x1[current_position + 1] * c1[current_position];
			*x1[0] = *d1[0] - *x1[1] * c1[0];
			// Tridiagonal matrix solution for correction - End
			System::Byte cnt_0;
			for (current_position = 0; current_position < vertex_array_length; current_position++)
				for (cnt_0 = 0; cnt_0 < 3; cnt_0++)
					x[current_position]->p[cnt_0] -= (x1[current_position]->p[cnt_0] * x[vertex_array_length - 1]->p[cnt_0]) / (1 + x1[vertex_array_length - 1]->p[cnt_0]);
			vertex_array_length++;
			*x[vertex_array_length - 1] = *x[0];
			if(end_condition_mode == 3) *x[vertex_array_length - 1] *= -1;
			for(current_position = 0; current_position < vertex_array_length; current_position++){
				delete x1[current_position];
			}
			delete []x1;
		}
		FlushCoefficients(2);
		coefficients = gcnew array<vector3D^, 2>((vertex_array_length - 1), 5);
		for(current_position = 0; current_position < (vertex_array_length - 1); current_position++){
			coefficients[current_position, 0] = gcnew vector3D(*vertices[current_position]);
			coefficients[current_position, 1] = gcnew vector3D(*x[current_position]);
			coefficients[current_position, 2] = gcnew vector3D((*vertices[current_position + 1] - *vertices[current_position]) * 3 - (*x[current_position]) * 2 - (*x[current_position + 1]));
			coefficients[current_position, 3] = gcnew vector3D((*vertices[current_position] - *vertices[current_position + 1]) * 2 + (*x[current_position]) + (*x[current_position + 1]));
			coefficients[current_position, 4] = gcnew vector3D(*x[current_position + 1]);
		}
		delete []a;
		delete []b;
		delete []c;
		delete []c1;
		for(current_position = 0; current_position < vertex_array_length; current_position++){
			delete d[current_position];
			delete d1[current_position];
			delete x[current_position];
		}
		delete []d;
		delete []d1;
		delete []x;
	}

	void Object_Cubic_Spline::Sample(System::Double% scale){
		System::Byte cnt;
		System::Double side_vec_mag;
		System::Double param;
		System::UInt32 side_length;
		vector3D side_vector;
		FlushSamples();
		s_current_position = 0;
		s_vertex_array_length = 0;
		for(current_position = 0; current_position < (vertex_array_length - 1); current_position++){
			side_vector = *vertices[current_position + 1] - *vertices[current_position];
			side_vec_mag = side_vector.Magnitude();
			side_length = (System::UInt32)(Math::Round(Math::Pow(((side_vec_mag + (2 * coefficients[current_position, 4]->Magnitude() - side_vector.DotProduct(*coefficients[current_position, 4]) / side_vec_mag) + (2 * coefficients[current_position, 1]->Magnitude() - side_vector.DotProduct(*coefficients[current_position, 1]) / side_vec_mag)) * CUBIC_SAMPLE * scale), SAMPLE_DECAY)));
			s_vertex_array_length += side_length;
		}
		sampled_vertices = gcnew array<vector3D^>(s_vertex_array_length);
		s_vertex_array_length = 0;
		for(current_position = 0; current_position < (vertex_array_length - 1); current_position++){
			param = 0;
			side_vector = *vertices[current_position + 1] - *vertices[current_position];
			side_vec_mag = side_vector.Magnitude();
			side_length = (System::UInt32)(Math::Round(Math::Pow(((side_vec_mag + (2 * coefficients[current_position, 4]->Magnitude() - side_vector.DotProduct(*coefficients[current_position, 4]) / side_vec_mag) + (2 * coefficients[current_position, 1]->Magnitude() - side_vector.DotProduct(*coefficients[current_position, 1]) / side_vec_mag)) * CUBIC_SAMPLE * scale), SAMPLE_DECAY)));
			s_vertex_array_length += side_length;
			for(; s_current_position < s_vertex_array_length; s_current_position++){
				sampled_vertices[s_current_position] = gcnew vector3D();
				for(cnt = 0; cnt < 4; cnt++)
					*sampled_vertices[s_current_position] += coefficients[current_position, cnt] * Math::Pow(param, cnt);
				param += 1 / (System::Double)(side_length - 1);
			}
		}
		current_position++;
	}

	void Object_Cubic_Spline::CubicScale(vector3D% scale_vector){
		if(!end_condition_mode){
			start_derivative.Scale(scale_vector);
			end_derivative.Scale(scale_vector);
		}
	}

	void Object_Cubic_Spline::CubicRotate(vector3D% rotation_vector, System::Double% theta){
		if(!end_condition_mode){
			start_derivative.Rotate(rotation_vector, theta);
			end_derivative.Rotate(rotation_vector, theta);
		}
	}

	Object_Cubic_Spline::~Object_Cubic_Spline(void){
		FlushCoefficients(0);
	}

	/******************************************************************
	***************Methods of Object_Bezier_Curve class****************
	*******************************************************************/

	Object_Bezier_Curve::Object_Bezier_Curve(System::UInt32% color_arg) : Sampled_Object_PL_Based(color_arg, 7){}

	void Object_Bezier_Curve::Sample(System::Double% scale){
		FlushSamples();
		s_vertex_array_length = (System::UInt32)(Math::Round(Math::Pow((polygon_length * BEZIER_SAMPLE * scale), SAMPLE_DECAY)));
		if(s_vertex_array_length > 1){
			sampled_vertices = gcnew array<vector3D^>(s_vertex_array_length);
			System::Double param = 0;
			for(s_current_position = 0; s_current_position < s_vertex_array_length; s_current_position++)
				sampled_vertices[s_current_position] = gcnew vector3D();
			for(s_current_position = 0; s_current_position < s_vertex_array_length; s_current_position++){
				for(current_position = 0; current_position < vertex_array_length; current_position++) 
					*sampled_vertices[s_current_position] += vertices[current_position] * (Math::Pow(param, current_position) * Math::Pow((1 - param), (vertex_array_length - (current_position + 1))) * (System::Double)Factorial(vertex_array_length - 1) / (System::Double)(Factorial(current_position) * Factorial(vertex_array_length - (current_position + 1))));
				param += 1 / (System::Double)(s_vertex_array_length - 1);
			}
		}
	}

	void Object_Bezier_Curve::PolygonLengthUpdate(void){
		polygon_length = 0;
		for(current_position = 1; current_position < vertex_array_length; current_position++)
			polygon_length += (*vertices[current_position] - *vertices[current_position - 1]).Magnitude();
	}

	Object_Bezier_Curve::~Object_Bezier_Curve(void){}

	/******************************************************************
	******************Methods of Object_BSpline class******************
	*******************************************************************/

	Object_BSpline::Object_BSpline(System::UInt32% color_arg) : Sampled_Object_PL_Based(color_arg, 8){
		order = 0;
	}

	void Object_BSpline::Sample(System::Double% scale){
		System::UInt32 cnt0;
		FlushSamples();
		if(order > 2){
			s_vertex_array_length = (System::UInt32)(Math::Round(Math::Pow((polygon_length * BSPLINE_SAMPLE * scale), SAMPLE_DECAY)));
			if(s_vertex_array_length > 1){
				sampled_vertices = gcnew array<vector3D^>(s_vertex_array_length);
				for(s_current_position = 0; s_current_position < s_vertex_array_length; s_current_position++)
					sampled_vertices[s_current_position] = gcnew vector3D();
				System::Double param = 0;
				if(!mode) param = order - 1;
				for(s_current_position = 0; s_current_position < s_vertex_array_length; s_current_position++){	
					BSplineBasis(param);
					for(current_position = 0; current_position < vertex_array_length; current_position++) 
						*sampled_vertices[s_current_position] += vertices[current_position] * bspline_basis[current_position][order - 1];
					param += (System::Double)(vertex_array_length - order + 1) / (System::Double)(s_vertex_array_length - 1);
					for(cnt0 = 0; cnt0 < vertex_array_length + order - 1; cnt0++){
						delete []bspline_basis[cnt0];
					}
					delete []bspline_basis;
				}
				if(mode) *sampled_vertices[s_vertex_array_length - 1] = *vertices[vertex_array_length - 1];
			}
		}
		else{
			s_vertex_array_length = vertex_array_length;
			if(s_vertex_array_length > 1){
				sampled_vertices = gcnew array<vector3D^>(s_vertex_array_length);
				for(s_current_position = 0; s_current_position < s_vertex_array_length; s_current_position++)
					sampled_vertices[s_current_position] = gcnew vector3D(*vertices[s_current_position]);
			}
		}
	}

	void Object_BSpline::BSplineAddVertex(vector3D% new_vertex){
		order++;
		AddVertex(new_vertex);
		KnotUpdate();
	}

	void Object_BSpline::KnotUpdate(void){
		delete []knot;
		knot = new System::UInt32[vertex_array_length + order];
		System::UInt32 cnt0;
		if(mode){
			for(cnt0 = 0; cnt0 < order; cnt0++){
				knot[cnt0] = 0;
				knot[vertex_array_length + order - 1 - cnt0] = vertex_array_length - order + 1;
			}
			for(; cnt0 < vertex_array_length; cnt0++) knot[cnt0] = cnt0 - order + 1;
		}
		else for(cnt0 = 0; cnt0 < (order + vertex_array_length); cnt0++) knot[cnt0] = cnt0;
	}

	void Object_BSpline::PolygonLengthUpdate(void){
		polygon_length = 0;
		for(current_position = 1; current_position < vertex_array_length; current_position++)
			polygon_length += (*vertices[current_position] - *vertices[current_position - 1]).Magnitude();
	}

	void Object_BSpline::BSplineBasis(System::Double% param){
		bspline_basis = new System::Double*[vertex_array_length + order - 1];
		System::UInt32 cnt0;
		System::UInt32 cnt1;
		for(cnt0 = 0; cnt0 < vertex_array_length + order - 1; cnt0++){
			bspline_basis[cnt0] = new System::Double[order];
		}
		for(cnt0 = 0; cnt0 < vertex_array_length + order - 1; cnt0++){
			if((knot[cnt0] <= param) && (knot[cnt0 + 1] > param)) bspline_basis[cnt0][0] = 1;
			else bspline_basis[cnt0][0] = 0;
		}
		for(cnt1 = 1; cnt1 < order; cnt1++){
			for(cnt0 = 0; cnt0 < vertex_array_length + order - cnt1 - 1; cnt0++){
				System::Double return_val0 = (param - (System::Double)knot[cnt0]) * bspline_basis[cnt0][cnt1 - 1];
				if(return_val0 != 0) return_val0 /= (System::Double)(knot[cnt0 + cnt1] - knot[cnt0]);
				System::Double return_val1 = ((System::Double)knot[cnt0 + cnt1 + 1] - param) * bspline_basis[cnt0 + 1][cnt1 - 1];
				if(return_val1 != 0) return_val1 /= (System::Double)(knot[cnt0 + cnt1 + 1] - knot[cnt0 + 1]);
				bspline_basis[cnt0][cnt1] = return_val0 + return_val1;
			}
		}
	}

	Object_BSpline::~Object_BSpline(void){
		delete []knot;
	}

	/******************************************************************
	********************Methods of Object_Mesh class*******************
	*******************************************************************/

	Object_Mesh::Object_Mesh(System::UInt32% color_arg) : Screen_Object(color_arg, 9){
		Construct();
	}

	Object_Mesh::Object_Mesh(System::UInt32% color_arg, System::Byte id) : Screen_Object(color_arg, id){
		Construct();
	}

	void Object_Mesh::Construct(){
		vertex_mode = false;
		current_position_0 = current_position_1 = 0;
		vertex_array_length_0 = 0;
		vertex_array_length_1 = 1;
		vertex_array_max_length_0 = 4;
		vertex_array_max_length_1 = 1;
		vertices = gcnew array<vector3D^, 2>(4, 1);
	}

	void Object_Mesh::AddVertex(vector3D% new_vertex){
		if(vertex_mode){
			if(current_position_0 == vertex_array_length_0){
				current_position_1++;
				if(current_position_1 == vertex_array_max_length_1){
					array<vector3D^, 2>^ temporary_array = gcnew array<vector3D^, 2>(vertex_array_length_0, (vertex_array_max_length_1 += 4));
					for(current_position_0 = 0; current_position_0 < vertex_array_length_0; current_position_0++)
						for(current_position_1 = 0; current_position_1 < vertex_array_length_1; current_position_1++)
							temporary_array[current_position_0, current_position_1] = vertices[current_position_0, current_position_1];
					delete []vertices;
					vertices = temporary_array;
					vertex_array_length_1++;					
				}
				else vertex_array_length_1++;
				for(current_position_0 = 0; current_position_0 < vertex_array_length_0; current_position_0++)
					vertices[current_position_0, (vertex_array_length_1 - 1)] = vertices[current_position_0, (vertex_array_length_1 - 2)];
				current_position_0 = 0;
			}
			vertices[current_position_0++, current_position_1] = gcnew vector3D(new_vertex);
		}
		else{
			if(current_position_0 >= vertex_array_max_length_0){
				array<vector3D^, 2>^ temporary_array = gcnew array<vector3D^, 2>((vertex_array_max_length_0 += 4), 1);
				for(current_position_0 = 0; current_position_0 < vertex_array_length_0; current_position_0++)
					temporary_array[current_position_0, 0] = vertices[current_position_0, 0];
				delete []vertices;
				vertices = temporary_array;
			}
			vertices[current_position_0++, 0] = gcnew vector3D(new_vertex);
			vertex_array_length_0++;
		}
	}

	void Object_Mesh::MeshShift(vector3D% shift_vector){
		for(current_position_0 = 0; current_position_0 < vertex_array_length_0; current_position_0++)
			for(current_position_1 = 0; current_position_1 < vertex_array_length_1; current_position_1++)
				*vertices[current_position_0, current_position_1] += shift_vector;
	}

	void Object_Mesh::MeshScale(vector3D% scale_origin, vector3D% scale_vector){
		for(current_position_0 = 0; current_position_0 < vertex_array_length_0; current_position_0++)
			for(current_position_1 = 0; current_position_1 < vertex_array_length_1; current_position_1++)
				(vertices[current_position_0, current_position_1])->Scale(scale_origin, scale_vector);
	}

	void Object_Mesh::MeshRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		for(current_position_0 = 0; current_position_0 < vertex_array_length_0; current_position_0++)
			for(current_position_1 = 0; current_position_1 < vertex_array_length_1; current_position_1++)
				(vertices[current_position_0, current_position_1])->Rotate(r_v_start, r_v_end, theta);
	}

	void Object_Mesh::ClearExtraSpace(void){
		if(vertex_mode){
			current_position_1 --;
			array<vector3D^, 2>^ temporary_array = gcnew array<vector3D^, 2>(vertex_array_length_0, (current_position_1 + 1));
			for(current_position_0 = 0; current_position_0 < vertex_array_length_0; current_position_0++)
				for(vertex_array_length_1 = 0; vertex_array_length_1 <= current_position_1; vertex_array_length_1++)
					temporary_array[current_position_0, vertex_array_length_1] = vertices[current_position_0, vertex_array_length_1];
			delete []vertices;
			vertices = temporary_array;
		}
		else{
			current_position_0 -= 2;
			array<vector3D^, 2>^ temporary_array = gcnew array<vector3D^, 2>((current_position_0 + 1), 1);
			for(vertex_array_length_0 = 0; vertex_array_length_0 <= current_position_0; vertex_array_length_0++)
				temporary_array[vertex_array_length_0, 0] = vertices[vertex_array_length_0, 0];
			delete []vertices;
			vertices = temporary_array;
			current_position_0++;
		}
	}

	Object_Mesh::~Object_Mesh(void){
		for(current_position_0 = 0; current_position_0 < vertex_array_length_0; current_position_0++)
			for(current_position_1 = 0; current_position_1 < vertex_array_length_1; current_position_1++)
				delete vertices[current_position_0, current_position_1];
		delete []vertices;
	}

	/******************************************************************
	***************Methods of Sampled_Object_Surf class****************
	*******************************************************************/

	Sampled_Object_Surf::Sampled_Object_Surf(System::UInt32% color_arg, System::Byte id) : Screen_Object(color_arg, id){
		s_vertex_array_length_00 = 0;
		s_vertex_array_length_01 = 0;
		s_vertex_array_length_10 = 0;
		s_vertex_array_length_11 = 0;
		sampled_vertices_0 = gcnew array<vector3D^, 2>(0, 0);
		sampled_vertices_1 = gcnew array<vector3D^, 2>(0, 0);
	}

	void Sampled_Object_Surf::FlushSamples(void){
		if(s_vertex_array_length_00 > 1){
			for(s_current_position_00 = 0; s_current_position_00 < s_vertex_array_length_00; s_current_position_00++)
				for(s_current_position_01 = 0; s_current_position_01 < s_vertex_array_length_01; s_current_position_01++)
					delete sampled_vertices_0[s_current_position_00, s_current_position_01];
			delete []sampled_vertices_0;
		}
		if(s_vertex_array_length_10 > 1){
			for(s_current_position_10 = 0; s_current_position_10 < s_vertex_array_length_10; s_current_position_10++)
				for(s_current_position_11 = 0; s_current_position_11 < s_vertex_array_length_11; s_current_position_11++)
					delete sampled_vertices_1[s_current_position_10, s_current_position_11];
			delete []sampled_vertices_1;
		}
	}

	Sampled_Object_Surf::~Sampled_Object_Surf(void){
		FlushSamples();
	}

	/******************************************************************
	************Methods of Sampled_Object_Mesh_Based class*************
	*******************************************************************/

	Sampled_Object_Mesh_Based::Sampled_Object_Mesh_Based(System::UInt32% color_arg, System::Byte id) : Object_Mesh(color_arg, id){
		s_vertex_array_length_00 = 0;
		s_vertex_array_length_01 = 0;
		s_vertex_array_length_10 = 0;
		s_vertex_array_length_11 = 0;
		sampled_vertices_0 = gcnew array<vector3D^, 2>(0, 0);
		sampled_vertices_1 = gcnew array<vector3D^, 2>(0, 0);
	}

	void Sampled_Object_Mesh_Based::FlushSamples(void){
		if(s_vertex_array_length_00 > 1){
			for(s_current_position_00 = 0; s_current_position_00 < s_vertex_array_length_00; s_current_position_00++)
				for(s_current_position_01 = 0; s_current_position_01 < s_vertex_array_length_01; s_current_position_01++)
					delete sampled_vertices_0[s_current_position_00, s_current_position_01];
			delete []sampled_vertices_0;
		}
		if(s_vertex_array_length_10 > 1){
			for(s_current_position_10 = 0; s_current_position_10 < s_vertex_array_length_10; s_current_position_10++)
				for(s_current_position_11 = 0; s_current_position_11 < s_vertex_array_length_11; s_current_position_11++)
					delete sampled_vertices_1[s_current_position_10, s_current_position_11];
			delete []sampled_vertices_1;
		}
	}

	Sampled_Object_Mesh_Based::~Sampled_Object_Mesh_Based(void){
		FlushSamples();
	}

	/******************************************************************
	***************Methods of Object_Bilinear_Surf class***************
	*******************************************************************/

	Object_Bilinear_Surf::Object_Bilinear_Surf(System::UInt32% color_arg) : Sampled_Object_Surf(color_arg, 10){
		System::Byte cnt_0;
		vertices = gcnew array<vector3D^>(4);
		for(cnt_0 = 0; cnt_0 < 4; cnt_0++) vertices[cnt_0] = gcnew vector3D();
	}

	void Object_Bilinear_Surf::Sample(System::Double% scale){
		FlushSamples();
		System::Double param_0 = 0;
		System::Double param_1;
		s_vertex_array_length_00 = (System::UInt32)(Math::Round(Math::Pow((polygon_length_0 * BILINEAR_SAMPLE_0 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_01 = (System::UInt32)(Math::Round(Math::Pow((polygon_length_1 * BILINEAR_SAMPLE_1 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_10 = (System::UInt32)(Math::Round(Math::Pow((polygon_length_1 * BILINEAR_SAMPLE_0 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_11 = (System::UInt32)(Math::Round(Math::Pow((polygon_length_0 * BILINEAR_SAMPLE_1 * scale), SAMPLE_DECAY))) + 1;
		if(s_vertex_array_length_00 > 1){
			sampled_vertices_0 = gcnew array<vector3D^, 2>(s_vertex_array_length_00, s_vertex_array_length_01);
			for(s_current_position_00 = 0; s_current_position_00 < s_vertex_array_length_00; s_current_position_00++){
				param_1 = 0;
				for(s_current_position_01 = 0; s_current_position_01 < s_vertex_array_length_01; s_current_position_01++){
					sampled_vertices_0[s_current_position_00, s_current_position_01] = gcnew vector3D(vertices[0] * (1 - param_0) * (1 - param_1) + vertices[1] * param_0 * (1 - param_1) + vertices[2] * (1 - param_0) * param_1 + vertices[3] * param_0 * param_1);
					param_1 += 1 / (System::Double)(s_vertex_array_length_01 - 1);
				}
				param_0 += 1 / (System::Double)(s_vertex_array_length_00 - 1);
			}
		}
		if(s_vertex_array_length_10 > 1){
			sampled_vertices_1 = gcnew array<vector3D^, 2>(s_vertex_array_length_10, s_vertex_array_length_11);
			param_0 = 0;
			for(s_current_position_10 = 0; s_current_position_10 < s_vertex_array_length_10; s_current_position_10++){
				param_1 = 0;
				for(s_current_position_11 = 0; s_current_position_11 < s_vertex_array_length_11; s_current_position_11++){
					sampled_vertices_1[s_current_position_10, s_current_position_11] = gcnew vector3D(vertices[0] * (1 - param_0) * (1 - param_1) + vertices[1] * (1 - param_0) * param_1 + vertices[2] * param_0 * (1 - param_1) + vertices[3] * param_0 * param_1);
					param_1 += 1 / (System::Double)(s_vertex_array_length_11 - 1);
				}
				param_0 += 1 / (System::Double)(s_vertex_array_length_10 - 1);
			}
		}
	}

	void Object_Bilinear_Surf::BilinearShift(vector3D% shift_vector){
		System::Byte cnt_0;
		for(cnt_0 = 0; cnt_0 < 4; cnt_0++) vertices[cnt_0] += shift_vector;
	}

	void Object_Bilinear_Surf::BilinearScale(vector3D% scale_origin, vector3D% scale_vector){
		System::Byte cnt_0;
		for(cnt_0 = 0; cnt_0 < 4; cnt_0++) vertices[cnt_0]->Scale(scale_origin, scale_vector);
	}

	void Object_Bilinear_Surf::BilinearRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		System::Byte cnt_0;
		for(cnt_0 = 0; cnt_0 < 4; cnt_0++) vertices[cnt_0]->Rotate(r_v_start, r_v_end, theta);
	}

	void Object_Bilinear_Surf::PolygonLengthUpdate(void){
		System::Double temp_length;
		polygon_length_0 = (*vertices[0] - *vertices[1]).Magnitude();
		temp_length = (*vertices[2] - *vertices[3]).Magnitude();
		if(temp_length > polygon_length_0) polygon_length_0 = temp_length;
		polygon_length_1 = (*vertices[0] - *vertices[2]).Magnitude();
		temp_length = (*vertices[1] - *vertices[3]).Magnitude();
		if(temp_length > polygon_length_1) polygon_length_1 = temp_length;
	}

	Object_Bilinear_Surf::~Object_Bilinear_Surf(void){
		System::Byte cnt_0;
		for(cnt_0 = 0; cnt_0 < 4; cnt_0++) delete vertices[cnt_0];
		delete []vertices;
	}

	/******************************************************************
	****************Methods of Object_Bicubic_Surf class***************
	*******************************************************************/

	Object_Bicubic_Surf::Object_Bicubic_Surf(System::UInt32% color_arg) : Sampled_Object_Surf(color_arg, 13){
		System::Byte cnt_0;
		vertices = gcnew array<vector3D^>(16);
		for(cnt_0 = 0; cnt_0 < 16; cnt_0++) vertices[cnt_0] = gcnew vector3D();
	}

	void Object_Bicubic_Surf::Sample(System::Double% scale){
		System::Double f1_0, f2_0, f3_0, f4_0, f1_1, f2_1, f3_1, f4_1;
		System::Double param_0 = 0;
		System::Double param_1;
		FlushSamples();
		s_vertex_array_length_00 = (System::UInt32)(Math::Round(Math::Pow((polygon_length_0 * BILINEAR_SAMPLE_0 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_01 = (System::UInt32)(Math::Round(Math::Pow((polygon_length_1 * BICUBIC_SAMPLE_1 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_10 = (System::UInt32)(Math::Round(Math::Pow((polygon_length_1 * BILINEAR_SAMPLE_0 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_11 = (System::UInt32)(Math::Round(Math::Pow((polygon_length_0 * BICUBIC_SAMPLE_1 * scale), SAMPLE_DECAY))) + 1;
		if(s_vertex_array_length_00 > 1){
			sampled_vertices_0 = gcnew array<vector3D^, 2>(s_vertex_array_length_00, s_vertex_array_length_01);
			for(s_current_position_00 = 0; s_current_position_00 < s_vertex_array_length_00; s_current_position_00++){
				f1_0 = F1(param_0);
				f2_0 = F2(param_0);
				f3_0 = F3(param_0);
				f4_0 = F4(param_0);
				param_1 = 0;
				for(s_current_position_01 = 0; s_current_position_01 < s_vertex_array_length_01; s_current_position_01++){
					f1_1 = F1(param_1);
					f2_1 = F2(param_1);
					f3_1 = F3(param_1);
					f4_1 = F4(param_1);
					sampled_vertices_0[s_current_position_00, s_current_position_01] = gcnew vector3D(vertices[0] * f1_0 * f1_1 + vertices[1] * f1_0 * f2_1 + vertices[2] * f2_0 * f1_1 + vertices[3] * f2_0 * f2_1 + vertices[4] * f1_0 * f3_1 + vertices[5] * f1_0 * f4_1 + vertices[6] * f2_0 * f3_1 + vertices[7] * f2_0 * f4_1 + vertices[8] * f3_0 * f1_1 + vertices[9] * f3_0 * f2_1 + vertices[10] * f4_0 * f1_1 + vertices[11] * f4_0 * f2_1 + vertices[12] * f3_0 * f3_1 + vertices[13] * f3_0 * f4_1 + vertices[14] * f4_0 * f3_1 + vertices[15] * f4_0 * f4_1);
					param_1 += 1 / (System::Double)(s_vertex_array_length_01 - 1);
				}
				param_0 += 1 / (System::Double)(s_vertex_array_length_00 - 1);
			}
		}
		if(s_vertex_array_length_10 > 1){
			sampled_vertices_1 = gcnew array<vector3D^, 2>(s_vertex_array_length_10, s_vertex_array_length_11);
			param_1 = 0;
			for(s_current_position_10 = 0; s_current_position_10 < s_vertex_array_length_10; s_current_position_10++){
				f1_1 = F1(param_1);
				f2_1 = F2(param_1);
				f3_1 = F3(param_1);
				f4_1 = F4(param_1);
				param_0 = 0;
				for(s_current_position_11 = 0; s_current_position_11 < s_vertex_array_length_11; s_current_position_11++){
					f1_0 = F1(param_0);
					f2_0 = F2(param_0);
					f3_0 = F3(param_0);
					f4_0 = F4(param_0);
					sampled_vertices_1[s_current_position_10, s_current_position_11] = gcnew vector3D(vertices[0] * f1_0 * f1_1 + vertices[1] * f1_0 * f2_1 + vertices[2] * f2_0 * f1_1 + vertices[3] * f2_0 * f2_1 + vertices[4] * f1_0 * f3_1 + vertices[5] * f1_0 * f4_1 + vertices[6] * f2_0 * f3_1 + vertices[7] * f2_0 * f4_1 + vertices[8] * f3_0 * f1_1 + vertices[9] * f3_0 * f2_1 + vertices[10] * f4_0 * f1_1 + vertices[11] * f4_0 * f2_1 + vertices[12] * f3_0 * f3_1 + vertices[13] * f3_0 * f4_1 + vertices[14] * f4_0 * f3_1 + vertices[15] * f4_0 * f4_1);
					param_0 += 1 / (System::Double)(s_vertex_array_length_11 - 1);
				}
				param_1 += 1 / (System::Double)(s_vertex_array_length_10 - 1);
			}
		}
	}

	void Object_Bicubic_Surf::BicubicShift(vector3D% shift_vector){
		System::Byte cnt_0;
		for(cnt_0 = 0; cnt_0 < 4; cnt_0++) vertices[cnt_0] += shift_vector;
	}

	void Object_Bicubic_Surf::BicubicScale(vector3D% scale_origin, vector3D% scale_vector){
		System::Byte cnt_0;
		for(cnt_0 = 0; cnt_0 < 4; cnt_0++) vertices[cnt_0]->Scale(scale_origin, scale_vector);
		for(; cnt_0 < 16; cnt_0++) vertices[cnt_0]->Scale(scale_vector);
	}

	void Object_Bicubic_Surf::BicubicRotate(vector3D% r_v_start, vector3D% r_v_end, System::Double% theta){
		System::Byte cnt_0;
		vector3D rotator = r_v_end - r_v_start;
		for(cnt_0 = 0; cnt_0 < 4; cnt_0++) vertices[cnt_0]->Rotate(r_v_start, r_v_end, theta);
		for(; cnt_0 < 16; cnt_0++) vertices[cnt_0]->Rotate(rotator, theta);
	}

	void Object_Bicubic_Surf::PolygonLengthUpdate(void){
		System::Double temp_length;
		polygon_length_0 = (*vertices[0] - *vertices[1]).Magnitude();
		temp_length = (*vertices[2] - *vertices[3]).Magnitude();
		if(temp_length > polygon_length_0) polygon_length_0 = temp_length;
		polygon_length_1 = (*vertices[0] - *vertices[2]).Magnitude();
		temp_length = (*vertices[1] - *vertices[3]).Magnitude();
		if(temp_length > polygon_length_1) polygon_length_1 = temp_length;
	}

	System::Double Object_Bicubic_Surf::F1(System::Double% param){
		return (2*Math::Pow(param, 3) - 3*Math::Pow(param, 2) + 1);
	}

	System::Double Object_Bicubic_Surf::F2(System::Double% param){
		return (3*Math::Pow(param, 2) - 2*Math::Pow(param, 3));
	}

	System::Double Object_Bicubic_Surf::F3(System::Double% param){
		return (Math::Pow(param, 3) - 2*Math::Pow(param, 2) + param);
	}

	System::Double Object_Bicubic_Surf::F4(System::Double% param){
		return (Math::Pow(param, 3) - Math::Pow(param, 2));
	}

	Object_Bicubic_Surf::~Object_Bicubic_Surf(void){
		System::Byte cnt_0;
		for(cnt_0 = 0; cnt_0 < 16; cnt_0++) delete vertices[cnt_0];
		delete []vertices;
	}

	/******************************************************************
	****************Methods of Object_Bezier_Surf class****************
	*******************************************************************/

	Object_Bezier_Surf::Object_Bezier_Surf(System::UInt32% color_arg) : Sampled_Object_Mesh_Based(color_arg, 11){}

	void Object_Bezier_Surf::Sample(System::Double% scale){
		System::Double param_0 = 0;
		System::Double param_1;
		FlushSamples();
		s_vertex_array_length_00 = (System::UInt32)(Math::Round(Math::Pow((max_polygon_length_0 * BILINEAR_SAMPLE_0 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_01 = (System::UInt32)(Math::Round(Math::Pow((max_polygon_length_1 * BILINEAR_SAMPLE_1 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_10 = (System::UInt32)(Math::Round(Math::Pow((max_polygon_length_1 * BILINEAR_SAMPLE_0 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_11 = (System::UInt32)(Math::Round(Math::Pow((max_polygon_length_0 * BILINEAR_SAMPLE_1 * scale), SAMPLE_DECAY))) + 1;
		if(s_vertex_array_length_00 > 1){
			sampled_vertices_0 = gcnew array<vector3D^, 2>(s_vertex_array_length_00, s_vertex_array_length_01);
			for(s_current_position_00 = 0; s_current_position_00 < s_vertex_array_length_00; s_current_position_00++)
				for(s_current_position_01 = 0; s_current_position_01 < s_vertex_array_length_01; s_current_position_01++)
					sampled_vertices_0[s_current_position_00, s_current_position_01] = gcnew vector3D();
			for(s_current_position_00 = 0; s_current_position_00 < s_vertex_array_length_00; s_current_position_00++){
				param_1 = 0;
				for(s_current_position_01 = 0; s_current_position_01 < s_vertex_array_length_01; s_current_position_01++){
					for(a_current_position_0 = 0; a_current_position_0 < vertex_array_length_0; a_current_position_0++)
						for(a_current_position_1 = 0; a_current_position_1 < vertex_array_length_1; a_current_position_1++)
							*sampled_vertices_0[s_current_position_00, s_current_position_01] += vertices[a_current_position_0, a_current_position_1] * (Math::Pow(param_0, a_current_position_0) * Math::Pow((1 - param_0), (vertex_array_length_0 - (a_current_position_0 + 1))) * (System::Double)Factorial(vertex_array_length_0 - 1) / (System::Double)(Factorial(a_current_position_0) * Factorial(vertex_array_length_0 - (a_current_position_0 + 1)))) * (Math::Pow(param_1, a_current_position_1) * Math::Pow((1 - param_1), (vertex_array_length_1 - (a_current_position_1 + 1))) * (System::Double)Factorial(vertex_array_length_1 - 1) / (System::Double)(Factorial(a_current_position_1) * Factorial(vertex_array_length_1 - (a_current_position_1 + 1))));
					param_1 += 1 / (System::Double)(s_vertex_array_length_01 - 1);
				}
				param_0 += 1 / (System::Double)(s_vertex_array_length_00 - 1);
			}
		}
		if(s_vertex_array_length_10 > 1){
			sampled_vertices_1 = gcnew array<vector3D^, 2>(s_vertex_array_length_10, s_vertex_array_length_11);;
			param_1 = 0;
			for(s_current_position_10 = 0; s_current_position_10 < s_vertex_array_length_10; s_current_position_10++)
				for(s_current_position_11 = 0; s_current_position_11 < s_vertex_array_length_11; s_current_position_11++)
					sampled_vertices_1[s_current_position_10, s_current_position_11] = gcnew vector3D();
			for(s_current_position_10 = 0; s_current_position_10 < s_vertex_array_length_10; s_current_position_10++){
				param_0 = 0;
				for(s_current_position_11 = 0; s_current_position_11 < s_vertex_array_length_11; s_current_position_11++){
					for(a_current_position_0 = 0; a_current_position_0 < vertex_array_length_0; a_current_position_0++)
						for(a_current_position_1 = 0; a_current_position_1 < vertex_array_length_1; a_current_position_1++)
							*sampled_vertices_1[s_current_position_10, s_current_position_11] += vertices[a_current_position_0, a_current_position_1] * (Math::Pow(param_0, a_current_position_0) * Math::Pow((1 - param_0), (vertex_array_length_0 - (a_current_position_0 + 1))) * (System::Double)Factorial(vertex_array_length_0 - 1) / (System::Double)(Factorial(a_current_position_0) * Factorial(vertex_array_length_0 - (a_current_position_0 + 1)))) * (Math::Pow(param_1, a_current_position_1) * Math::Pow((1 - param_1), (vertex_array_length_1 - (a_current_position_1 + 1))) * (System::Double)Factorial(vertex_array_length_1 - 1) / (System::Double)(Factorial(a_current_position_1) * Factorial(vertex_array_length_1 - (a_current_position_1 + 1))));
					param_0 += 1 / (System::Double)(s_vertex_array_length_11 - 1);
				}
				param_1 += 1 / (System::Double)(s_vertex_array_length_10 - 1);
			}
		}
	}

	void Object_Bezier_Surf::PolygonLengthUpdate(void){
		System::Double polygon_length = 0;
		max_polygon_length_0 = 0;
		max_polygon_length_1 = 0;
		for(a_current_position_1 = 0; a_current_position_1 < vertex_array_length_1; a_current_position_1++){
			for(a_current_position_0 = 1; a_current_position_0 < vertex_array_length_0; a_current_position_0++)
				polygon_length += (*vertices[a_current_position_0, a_current_position_1] - *vertices[(a_current_position_0 - 1), a_current_position_1]).Magnitude();
			if(polygon_length > max_polygon_length_0) max_polygon_length_0 = polygon_length;
		}
		polygon_length = 0;
		for(a_current_position_0 = 0; a_current_position_0 < vertex_array_length_0; a_current_position_0++){
			for(a_current_position_1 = 1; a_current_position_1 < vertex_array_length_1; a_current_position_1++)
				polygon_length += (*vertices[a_current_position_0, a_current_position_1] - *vertices[a_current_position_0, (a_current_position_1 - 1)]).Magnitude();
			if(polygon_length > max_polygon_length_1) max_polygon_length_1 = polygon_length;
		}
	}

	Object_Bezier_Surf::~Object_Bezier_Surf(void){}

	/******************************************************************
	****************Methods of Object_BSpline_Surf class***************
	*******************************************************************/

	Object_BSpline_Surf::Object_BSpline_Surf(System::UInt32% color_arg) : Sampled_Object_Mesh_Based(color_arg, 12){
		order_0 = 0;
		order_1 = 1;
	}

	void Object_BSpline_Surf::Sample(System::Double% scale){
		System::UInt32 cnt0;
		System::Double param_0;
		System::Double param_1;
		FlushSamples();
		s_vertex_array_length_00 = (System::UInt32)(Math::Round(Math::Pow((max_polygon_length_0 * BILINEAR_SAMPLE_0 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_01 = (System::UInt32)(Math::Round(Math::Pow((max_polygon_length_1 * BILINEAR_SAMPLE_1 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_10 = (System::UInt32)(Math::Round(Math::Pow((max_polygon_length_1 * BILINEAR_SAMPLE_0 * scale), SAMPLE_DECAY))) + 1;
		s_vertex_array_length_11 = (System::UInt32)(Math::Round(Math::Pow((max_polygon_length_0 * BILINEAR_SAMPLE_1 * scale), SAMPLE_DECAY))) + 1;
		if(s_vertex_array_length_00 > 1){
			sampled_vertices_0 = gcnew array<vector3D^, 2>(s_vertex_array_length_00, s_vertex_array_length_01);
			for(s_current_position_00 = 0; s_current_position_00 < s_vertex_array_length_00; s_current_position_00++)
				for(s_current_position_01 = 0; s_current_position_01 < s_vertex_array_length_01; s_current_position_01++)
					sampled_vertices_0[s_current_position_00, s_current_position_01] = gcnew vector3D();
			if(!mode) param_0 = order_0 - 1;
			else param_0 = 0;
			for(s_current_position_00 = 0; s_current_position_00 < s_vertex_array_length_00; s_current_position_00++){	
				BSplineBasis0(param_0, (s_current_position_00 == (s_vertex_array_length_00 - 1)));
				if(!mode) param_1 = order_1 - 1;
				else param_1 = 0;
				for(s_current_position_01 = 0; s_current_position_01 < s_vertex_array_length_01; s_current_position_01++){
					BSplineBasis1(param_1, (s_current_position_01 == (s_vertex_array_length_01 - 1)));
					for(a_current_position_0 = 0; a_current_position_0 < vertex_array_length_0; a_current_position_0++)
						for(a_current_position_1 = 0; a_current_position_1 < vertex_array_length_1; a_current_position_1++)
							*sampled_vertices_0[s_current_position_00, s_current_position_01] += vertices[a_current_position_0, a_current_position_1] * bspline_basis_0[a_current_position_0][order_0 - 1] * bspline_basis_1[a_current_position_1][order_1 - 1];
					param_1 += (System::Double)(vertex_array_length_1 - order_1 + 1) / (System::Double)(s_vertex_array_length_01 - 1);
					for(cnt0 = 0; cnt0 < vertex_array_length_1 + order_1 - 1; cnt0++){
						delete []bspline_basis_1[cnt0];
					}
					delete []bspline_basis_1;
				}
				param_0 += (System::Double)(vertex_array_length_0 - order_0 + 1) / (System::Double)(s_vertex_array_length_00 - 1);
				for(cnt0 = 0; cnt0 < vertex_array_length_0 + order_0 - 1; cnt0++){
					delete []bspline_basis_0[cnt0];
				}
				delete []bspline_basis_0;
			}
		}
		if(s_vertex_array_length_10 > 1){
			sampled_vertices_1 = gcnew array<vector3D^, 2>(s_vertex_array_length_10, s_vertex_array_length_11);;
			for(s_current_position_10 = 0; s_current_position_10 < s_vertex_array_length_10; s_current_position_10++)
				for(s_current_position_11 = 0; s_current_position_11 < s_vertex_array_length_11; s_current_position_11++)
					sampled_vertices_1[s_current_position_10, s_current_position_11] = gcnew vector3D();
			if(!mode) param_0 = order_0 - 1;
			else param_0 = 0;
			for(s_current_position_11 = 0; s_current_position_11 < s_vertex_array_length_11; s_current_position_11++){	
				BSplineBasis0(param_0, (s_current_position_11 == (s_vertex_array_length_11 - 1)));
				if(!mode) param_1 = order_1 - 1;
				else param_1 = 0;
				for(s_current_position_10 = 0; s_current_position_10 < s_vertex_array_length_10; s_current_position_10++){
					BSplineBasis1(param_1, (s_current_position_10 == (s_vertex_array_length_10 - 1)));
					for(a_current_position_0 = 0; a_current_position_0 < vertex_array_length_0; a_current_position_0++)
						for(a_current_position_1 = 0; a_current_position_1 < vertex_array_length_1; a_current_position_1++)
							*sampled_vertices_1[s_current_position_10, s_current_position_11] += vertices[a_current_position_0, a_current_position_1] * bspline_basis_0[a_current_position_0][order_0 - 1] * bspline_basis_1[a_current_position_1][order_1 - 1];
					param_1 += (System::Double)(vertex_array_length_1 - order_1 + 1) / (System::Double)(s_vertex_array_length_10 - 1);
					for(cnt0 = 0; cnt0 < vertex_array_length_1 + order_1 - 1; cnt0++){
						delete []bspline_basis_1[cnt0];
					}
					delete []bspline_basis_1;
				}
				param_0 += (System::Double)(vertex_array_length_0 - order_0 + 1) / (System::Double)(s_vertex_array_length_11 - 1);
				for(cnt0 = 0; cnt0 < vertex_array_length_0 + order_0 - 1; cnt0++){
					delete []bspline_basis_0[cnt0];
				}
				delete []bspline_basis_0;
			}
		}
	}

	void Object_BSpline_Surf::BSplineAddVertex(vector3D% new_vertex){
		AddVertex(new_vertex);
		if(vertex_mode){
			if(current_position_0 == 1){
				order_1++;
				KnotUpdate1();
			}
		}
		else{
			order_0++;
			KnotUpdate0();
		}		
	}

	void Object_BSpline_Surf::KnotUpdate0(void){
		delete []knot_0;
		knot_0 = new System::UInt32[vertex_array_length_0 + order_0];
		System::UInt32 cnt0;
		if(mode){
			for(cnt0 = 0; cnt0 < order_0; cnt0++){
				knot_0[cnt0] = 0;
				knot_0[vertex_array_length_0 + order_0 - 1 - cnt0] = vertex_array_length_0 - order_0 + 1;
			}
			for(; cnt0 < vertex_array_length_0; cnt0++) knot_0[cnt0] = cnt0 - order_0 + 1;
		}
		else for(cnt0 = 0; cnt0 < (order_0 + vertex_array_length_0); cnt0++) knot_0[cnt0] = cnt0;
	}

	void Object_BSpline_Surf::KnotUpdate1(void){
		delete []knot_1;
		knot_1 = new System::UInt32[vertex_array_length_1 + order_1];
		System::UInt32 cnt0;
		if(mode){
			for(cnt0 = 0; cnt0 < order_1; cnt0++){
				knot_1[cnt0] = 0;
				knot_1[vertex_array_length_1 + order_1 - 1 - cnt0] = vertex_array_length_1 - order_1 + 1;
			}
			for(; cnt0 < vertex_array_length_1; cnt0++) knot_1[cnt0] = cnt0 - order_1 + 1;
		}
		else for(cnt0 = 0; cnt0 < (order_1 + vertex_array_length_1); cnt0++) knot_1[cnt0] = cnt0;
	}

	void Object_BSpline_Surf::PolygonLengthUpdate(void){
		System::Double polygon_length = 0;
		max_polygon_length_0 = 0;
		max_polygon_length_1 = 0;
		for(a_current_position_1 = 0; a_current_position_1 < vertex_array_length_1; a_current_position_1++){
			for(a_current_position_0 = 1; a_current_position_0 < vertex_array_length_0; a_current_position_0++)
				polygon_length += (*vertices[a_current_position_0, a_current_position_1] - *vertices[(a_current_position_0 - 1), a_current_position_1]).Magnitude();
			if(polygon_length > max_polygon_length_0) max_polygon_length_0 = polygon_length;
		}
		polygon_length = 0;
		for(a_current_position_0 = 0; a_current_position_0 < vertex_array_length_0; a_current_position_0++){
			for(a_current_position_1 = 1; a_current_position_1 < vertex_array_length_1; a_current_position_1++)
				polygon_length += (*vertices[a_current_position_0, a_current_position_1] - *vertices[a_current_position_0, (a_current_position_1 - 1)]).Magnitude();
			if(polygon_length > max_polygon_length_1) max_polygon_length_1 = polygon_length;
		}
	}

	void Object_BSpline_Surf::BSplineBasis0(System::Double% param, System::Boolean% end){
		bspline_basis_0 = new System::Double*[vertex_array_length_0 + order_0 - 1];
		System::UInt32 cnt0;
		System::UInt32 cnt1;
		for(cnt0 = 0; cnt0 < vertex_array_length_0 + order_0 - 1; cnt0++){
			bspline_basis_0[cnt0] = new System::Double[order_0];
		}
		for(cnt0 = 0; cnt0 < vertex_array_length_0 + order_0 - 1; cnt0++){
			if((knot_0[cnt0] <= param) && (knot_0[cnt0 + 1] > param)) bspline_basis_0[cnt0][0] = 1;
			else bspline_basis_0[cnt0][0] = 0;
		}
		if(end && mode) bspline_basis_0[vertex_array_length_0 - 1][0] = 1;
		for(cnt1 = 1; cnt1 < order_0; cnt1++){
			for(cnt0 = 0; cnt0 < vertex_array_length_0 + order_0 - cnt1 - 1; cnt0++){
				System::Double return_val0 = (param - (System::Double)knot_0[cnt0]) * bspline_basis_0[cnt0][cnt1 - 1];
				if(return_val0 != 0) return_val0 /= (System::Double)(knot_0[cnt0 + cnt1] - knot_0[cnt0]);
				System::Double return_val1 = ((System::Double)knot_0[cnt0 + cnt1 + 1] - param) * bspline_basis_0[cnt0 + 1][cnt1 - 1];
				if(return_val1 != 0) return_val1 /= (System::Double)(knot_0[cnt0 + cnt1 + 1] - knot_0[cnt0 + 1]);
				bspline_basis_0[cnt0][cnt1] = return_val0 + return_val1;
			}
		}
	}

	void Object_BSpline_Surf::BSplineBasis1(System::Double% param, System::Boolean% end){
		bspline_basis_1 = new System::Double*[vertex_array_length_1 + order_1 - 1];
		System::UInt32 cnt0;
		System::UInt32 cnt1;
		for(cnt0 = 0; cnt0 < vertex_array_length_1 + order_1 - 1; cnt0++){
			bspline_basis_1[cnt0] = new System::Double[order_1];
		}
		for(cnt0 = 0; cnt0 < vertex_array_length_1 + order_1 - 1; cnt0++){
			if((knot_1[cnt0] <= param) && (knot_1[cnt0 + 1] > param)) bspline_basis_1[cnt0][0] = 1;
			else bspline_basis_1[cnt0][0] = 0;
		}
		if(end && mode) bspline_basis_1[vertex_array_length_1 - 1][0] = 1;
		for(cnt1 = 1; cnt1 < order_1; cnt1++){
			for(cnt0 = 0; cnt0 < vertex_array_length_1 + order_1 - cnt1 - 1; cnt0++){
				System::Double return_val0 = (param - (System::Double)knot_1[cnt0]) * bspline_basis_1[cnt0][cnt1 - 1];
				if(return_val0 != 0) return_val0 /= (System::Double)(knot_1[cnt0 + cnt1] - knot_1[cnt0]);
				System::Double return_val1 = ((System::Double)knot_1[cnt0 + cnt1 + 1] - param) * bspline_basis_1[cnt0 + 1][cnt1 - 1];
				if(return_val1 != 0) return_val1 /= (System::Double)(knot_1[cnt0 + cnt1 + 1] - knot_1[cnt0 + 1]);
				bspline_basis_1[cnt0][cnt1] = return_val0 + return_val1;
			}
		}
	}

	Object_BSpline_Surf::~Object_BSpline_Surf(void){
		delete []knot_0;
		delete []knot_1;
	}
}