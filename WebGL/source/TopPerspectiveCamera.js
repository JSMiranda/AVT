function TopPerspectiveCamera(){
	this.fov = 45.0;
	this.aspectRatio = gl.viewportWidth / gl.viewportHeight;
	this.near = 0.1;
	this.far = 40.1;

	this.pos = [16.0 , 10.5, 30.0];
	this.up = [0.0, 1.0, 0.0];
	this.at = [16.0, 10.5, 0.0];
}

TopPerspectiveCamera.prototype.load = function() {
	mat4.perspective(pMatrix, this.fov, this.aspectRatio, this.near, this.far);
	mat4.lookAt(mvMatrix, this.pos, this.at, this.up);
	// kinda hacky :s
	mat4.identity(viewMatrix);
	mat4.lookAt(viewMatrix, this.pos, this.at, this.up);
}

TopPerspectiveCamera.prototype.update = function() {}