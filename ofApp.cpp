#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 4);
	this->mesh = ico_sphere.getMesh();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		this->param_list.push_back(0);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->draw_mesh = this->mesh;
	this->line_mesh = this->mesh;

	for (int k = 0; k < 10; k++) {

		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

		auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.0025), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
		auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.0025), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
		auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.0025), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 0, 1));

		glm::vec3 location = glm::vec4(0, 0, 300, 0) * rotation_z * rotation_y * rotation_x;

		for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

			auto distance = glm::distance(location, this->draw_mesh.getVertex(i));
			if (distance < 50) {

				this->param_list[i] = 300;
			}
		}
	}

	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

		glm::vec3 vertex = this->draw_mesh.getVertex(i);
		vertex = glm::normalize(vertex) * (300 - this->param_list[i]);

		this->draw_mesh.setVertex(i, vertex);
		this->line_mesh.setVertex(i, vertex);
	}

	for (int i = 0; i < this->param_list.size(); i++) {

		this->param_list[i] -= 5;
		if (this->param_list[i] < 0) { this->param_list[i] = 0; }
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.37);
	ofRotateY(ofGetFrameNum() * 0.72);

	ofSeedRandom(39);

	for (int k = 0; k < 10; k++) {

		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

		auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.0025), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
		auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.0025), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
		auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.0025), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 0, 1));

		glm::vec3 location = glm::vec4(0, 0, 250, 0) * rotation_z * rotation_y * rotation_x;
		ofDrawSphere(location, 5);
	}

	ofSetColor(0);
	this->draw_mesh.draw();

	ofSetColor(255, 0, 0);
	this->line_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}