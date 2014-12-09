function FrogPerspectiveCamera(){
	this.fov = 45.0;
	this.aspectRatio = gl.viewportWidth / gl.viewportHeight;
	// FIXME: Change values below
	this.near = 0.1;
	this.far = 30.1;

	this.pos = [16.0 , 10.5, 30.0];
	this.up = [0.0, 1.0, 0.0];
	this.at = [16.0, 10.5, 0.0];
}

FrogPerspectiveCamera.prototype.load = function() {
	mat4.perspective(this.fov, this.aspectRatio, this.near, this.far, pMatrix);
	mat4.lookAt(this.pos, this.at, this.up, mvMatrix);
}

FrogPerspectiveCamera.prototype.update = function() {
	// TODO: Implement
}