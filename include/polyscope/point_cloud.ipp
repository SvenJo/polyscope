// Copyright 2017-2019, Nicholas Sharp and the Polyscope contributors. http://polyscope.run.
#pragma once

namespace polyscope {


// Shorthand to add a point cloud to polyscope
template <class T>
void registerPointCloud(std::string name, const T& points, bool replaceIfPresent) {
  PointCloud* s = new PointCloud(name, standardizeVectorArray<glm::vec3, 3>(points));
  bool success = registerStructure(s);
  if (!success) delete s;
}
template <class T>
void registerPointCloud2D(std::string name, const T& points, bool replaceIfPresent) {
  std::vector<glm::vec3> points3D(standardizeVectorArray<glm::vec3, 2>(points));
  for (auto& v : points3D) {
    v.z = 0.;
  }
  PointCloud* s = new PointCloud(name, points3D);
  bool success = registerStructure(s);
  if (!success) delete s;
}


// Shorthand to get a point cloud from polyscope
inline PointCloud* getPointCloud(std::string name) {
  return dynamic_cast<PointCloud*>(getStructure(PointCloud::structureTypeName, name));
}


// =====================================================
// ============== Quantities
// =====================================================


template <class T>
PointCloudColorQuantity* PointCloud::addColorQuantity(std::string name, const T& colors) {
  validateSize(colors, nPoints(), "point cloud color quantity " + name);
  return addColorQuantityImpl(name, standardizeVectorArray<glm::vec3, 3>(colors));
}


template <class T>
PointCloudScalarQuantity* PointCloud::addScalarQuantity(std::string name, const T& data, DataType type) {
  validateSize(data, nPoints(), "point cloud scalar quantity " + name);
  return addScalarQuantityImpl(name, standardizeArray<double, T>(data), type);
}

template <class T>
PointCloudVectorQuantity* PointCloud::addVectorQuantity(std::string name, const T& vectors, VectorType vectorType) {
  validateSize(vectors, nPoints(), "point cloud vector quantity " + name);
  return addVectorQuantityImpl(name, standardizeVectorArray<glm::vec3, 3>(vectors), vectorType);
}
template <class T>
PointCloudVectorQuantity* PointCloud::addVectorQuantity2D(std::string name, const T& vectors, VectorType vectorType) {
  validateSize(vectors, nPoints(), "point cloud vector quantity " + name);

  std::vector<glm::vec3> vectors3D(standardizeVectorArray<glm::vec3, 2>(vectors));
  for (auto& v : vectors3D) {
    v.z = 0.;
  }

  return addVectorQuantityImpl(name, vectors3D, vectorType);
}


} // namespace polyscope
