#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
	ofSetLineWidth(3);

	auto ico_sphere = ofIcoSpherePrimitive(300, 2);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	float noise_seed = ofRandom(1000);
	for (auto& triangle : this->triangles) {

		vector<glm::vec3> vertices;
		vector<glm::vec3> fill_vertices;
		for (int j = 0; j < 3; j++) {

			glm::vec3 location(triangle.getVertex(j).x, triangle.getVertex(j).y, triangle.getVertex(j).z);
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(location.y * 0.001 + ofGetFrameNum() * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
			location = glm::vec4(location, 0) * rotation_y;
			vertices.push_back(location);
			fill_vertices.push_back(location * 0.99);
		}

		ofFill();
		ofSetColor(239);

		ofBeginShape();
		ofVertices(fill_vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}