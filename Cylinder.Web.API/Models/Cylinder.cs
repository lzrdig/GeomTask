namespace Cylinder.API.Models
{
    public class Cylinder
    {
        public int cylinderId { get; set; }
        public Point3D bottomPt { get; set; }
        public Point3D topPt { get; set; }
        public double radius { get; set; }
        public double height { get; set; }
    }

    public class Vector3D
    {
        public int vectorId { get; set; }
        public double X { get; set; }
        public double Y { get; set; }
        public double Z { get; set; }
    }

    public class Point3D
    {
        public int pointId { get; set; }
        public double X { get; set; }
        public double Y { get; set; }
        public double Z { get; set; }
    }
}
