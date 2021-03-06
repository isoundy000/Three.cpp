//
//  Sphere.cpp
//  Three.cpp
//
//  Created by Saburo Okita on 26/06/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#include "Sphere.h"
#include "Box3.h"
#include "Math.h"
#include <glm/gtc/matrix_access.hpp>

namespace three {
    
    Sphere::Sphere() :
        center( glm::vec3(0, 0, 0) ),
        radius( 0.0f )
    {
    }
    
    
    Sphere::Sphere( glm::vec3 center, float radius ):
        center( center ),
        radius( radius )
    {
    }
    
    Sphere::~Sphere(){
    }
    
    
    Sphere::Sphere( const Sphere& rhs ) :
        center( rhs.center ),
        radius( rhs.radius )
    {
        
    }
    
    
    Sphere& Sphere::set( glm::vec3 center, float radius ) {
        this->center = center;
        this->radius = radius;
        return *this;
    }
    
    
    Sphere& Sphere::setFrom( std::vector<glm::vec3>& points, glm::vec3 center ) {
        this->center = center;
        
        float max_radius = 0.0;
        for( glm::vec3 point: points )
            max_radius = std::max( max_radius, glm::distance( this->center, point ));
        
        this->radius = max_radius;
        return *this;
    }
    
    Sphere& Sphere::setFrom( std::vector<glm::vec3>& points ) {
        Box3 box;
        this->center = box.setFrom( points ).center();
        
        float max_radius = 0.0;
        for( glm::vec3 point: points )
            max_radius = std::max( max_radius, glm::distance( this->center, point ));
        
        this->radius = max_radius;
        return *this;
    }
    
    Sphere& Sphere::operator=( const Sphere& others ) {
        if( this == &others )
            return *this;
        
        this->center = others.center;
        this->radius = others.radius;
        return *this;
    }
    
    bool Sphere::empty() {
        return this->radius <= 0.0;
    }
    
    
    bool Sphere::contains( glm::vec3 point ) {
        return glm::distance(point, this->center) <= (this->radius);
    }
    
    
    float Sphere::distanceTo( glm::vec3 point ) {
        return glm::distance( point, center ) - this->radius;
    }
    
    
    bool Sphere::doesIntersect( Sphere& sphere ) {
        float radius_sum = this->radius + sphere.radius;
        return glm::distance( sphere.center, this->center ) <= radius_sum;
    }
    
    glm::vec3 Sphere::clamp( glm::vec3 point ) {
        float distance = glm::distance(center, point);
        glm::vec3 result = point;
        
        if( distance > radius ) {
            result = glm::normalize( result - center );
            result *= radius;
            result += center;
        }
        
        return result;
    }
    
    Box3 Sphere::getBoundingBox() {
        Box3 box;
        box.set( center, center );
        box.expandByScalar( radius );
        return box;
    }
    
    Sphere& Sphere::applyMatrix( glm::mat4x4& mat ) {
        glm::vec4 temp = glm::vec4( center, 1 ) * mat;
        this->center   = glm::vec3( temp );
        this->radius   = this->radius * three::Math::getMaxScaleOnAxis( mat );
        return *this;
    }
    
    Sphere& Sphere::translate( glm::vec3 offset ) {
        this->center += offset;
        return *this;
    }
    
    bool Sphere::equals( Sphere& other ) {
        return center == other.center  && radius == other.radius;
    }
    
    Sphere Sphere::clone() {
        return Sphere(*this);
    }
}