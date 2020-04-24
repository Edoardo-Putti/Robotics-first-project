; Auto-generated. Do not edit!


(cl:in-package lla2enu-srv)


;//! \htmlinclude DistanceCalculator-request.msg.html

(cl:defclass <DistanceCalculator-request> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (x_obs
    :reader x_obs
    :initarg :x_obs
    :type cl:float
    :initform 0.0)
   (y_obs
    :reader y_obs
    :initarg :y_obs
    :type cl:float
    :initform 0.0))
)

(cl:defclass DistanceCalculator-request (<DistanceCalculator-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DistanceCalculator-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DistanceCalculator-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lla2enu-srv:<DistanceCalculator-request> is deprecated: use lla2enu-srv:DistanceCalculator-request instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <DistanceCalculator-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lla2enu-srv:x-val is deprecated.  Use lla2enu-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <DistanceCalculator-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lla2enu-srv:y-val is deprecated.  Use lla2enu-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'x_obs-val :lambda-list '(m))
(cl:defmethod x_obs-val ((m <DistanceCalculator-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lla2enu-srv:x_obs-val is deprecated.  Use lla2enu-srv:x_obs instead.")
  (x_obs m))

(cl:ensure-generic-function 'y_obs-val :lambda-list '(m))
(cl:defmethod y_obs-val ((m <DistanceCalculator-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lla2enu-srv:y_obs-val is deprecated.  Use lla2enu-srv:y_obs instead.")
  (y_obs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DistanceCalculator-request>) ostream)
  "Serializes a message object of type '<DistanceCalculator-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x_obs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y_obs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DistanceCalculator-request>) istream)
  "Deserializes a message object of type '<DistanceCalculator-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x_obs) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y_obs) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DistanceCalculator-request>)))
  "Returns string type for a service object of type '<DistanceCalculator-request>"
  "lla2enu/DistanceCalculatorRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DistanceCalculator-request)))
  "Returns string type for a service object of type 'DistanceCalculator-request"
  "lla2enu/DistanceCalculatorRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DistanceCalculator-request>)))
  "Returns md5sum for a message object of type '<DistanceCalculator-request>"
  "4e22589e822a5a44dc1faf02bd3b965d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DistanceCalculator-request)))
  "Returns md5sum for a message object of type 'DistanceCalculator-request"
  "4e22589e822a5a44dc1faf02bd3b965d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DistanceCalculator-request>)))
  "Returns full string definition for message of type '<DistanceCalculator-request>"
  (cl:format cl:nil "float64 x~%float64 y~%float64 x_obs~%float64 y_obs~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DistanceCalculator-request)))
  "Returns full string definition for message of type 'DistanceCalculator-request"
  (cl:format cl:nil "float64 x~%float64 y~%float64 x_obs~%float64 y_obs~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DistanceCalculator-request>))
  (cl:+ 0
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DistanceCalculator-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DistanceCalculator-request
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':x_obs (x_obs msg))
    (cl:cons ':y_obs (y_obs msg))
))
;//! \htmlinclude DistanceCalculator-response.msg.html

(cl:defclass <DistanceCalculator-response> (roslisp-msg-protocol:ros-message)
  ((distance
    :reader distance
    :initarg :distance
    :type cl:float
    :initform 0.0))
)

(cl:defclass DistanceCalculator-response (<DistanceCalculator-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DistanceCalculator-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DistanceCalculator-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lla2enu-srv:<DistanceCalculator-response> is deprecated: use lla2enu-srv:DistanceCalculator-response instead.")))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <DistanceCalculator-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lla2enu-srv:distance-val is deprecated.  Use lla2enu-srv:distance instead.")
  (distance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DistanceCalculator-response>) ostream)
  "Serializes a message object of type '<DistanceCalculator-response>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DistanceCalculator-response>) istream)
  "Deserializes a message object of type '<DistanceCalculator-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DistanceCalculator-response>)))
  "Returns string type for a service object of type '<DistanceCalculator-response>"
  "lla2enu/DistanceCalculatorResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DistanceCalculator-response)))
  "Returns string type for a service object of type 'DistanceCalculator-response"
  "lla2enu/DistanceCalculatorResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DistanceCalculator-response>)))
  "Returns md5sum for a message object of type '<DistanceCalculator-response>"
  "4e22589e822a5a44dc1faf02bd3b965d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DistanceCalculator-response)))
  "Returns md5sum for a message object of type 'DistanceCalculator-response"
  "4e22589e822a5a44dc1faf02bd3b965d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DistanceCalculator-response>)))
  "Returns full string definition for message of type '<DistanceCalculator-response>"
  (cl:format cl:nil "float64 distance~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DistanceCalculator-response)))
  "Returns full string definition for message of type 'DistanceCalculator-response"
  (cl:format cl:nil "float64 distance~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DistanceCalculator-response>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DistanceCalculator-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DistanceCalculator-response
    (cl:cons ':distance (distance msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DistanceCalculator)))
  'DistanceCalculator-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DistanceCalculator)))
  'DistanceCalculator-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DistanceCalculator)))
  "Returns string type for a service object of type '<DistanceCalculator>"
  "lla2enu/DistanceCalculator")