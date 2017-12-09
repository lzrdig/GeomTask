using System.Collections.Generic;
using System.Linq;
using System.Web.Http;
using System.Runtime.InteropServices;
using CylinderWrapperCSharp;
using System.Net.Http;
using System.Net;

namespace Cylinder.API.Controllers
{
    public class CylinderController : ApiController
    {
        private const string DllFilePath = @"Cylinder.dll";

        [DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl, EntryPoint = "GetDistFromPtToCylinder")]
        private extern static double GetDistFromPtToCylinder(double radius,
            double bottomX, double bottomY, double bottomZ,
            double topX, double topY, double topZ,
            double ptX, double ptY, double ptZ
            );

        /// <summary>
        /// GET api/cylinders
        /// Retrieves the list of Cylinder objects from a repository
        /// </summary>
        /// <returns>
        /// IEnumerable of Cyliner object
        /// </returns>
        public IEnumerable<Models.Cylinder> Get()
        {
            var cylinders = new Models.CylinderRepository();
            return cylinders.Retrieve();
        }

        // GET api/cylinders/radius
        public IEnumerable<Models.Cylinder> Get(double radius)
        {
            var cylinders = new Models.CylinderRepository();
            var cylinderList = cylinders.Retrieve();
            var filteredList = cylinderList.Where(t => t.radius == radius);
            return filteredList;
        }

        // GET api/cylinders/testptx/testpty/testptz
        public double Get(double testptx, double testpty, double testptz)
        {
            double distance = 0.0;

            double radius = 10.5;
            double bottomX = 0.0; double bottomY = 0.0; double bottomZ = 0.0;
            double topX = 0.0; double topY = 0.0; double topZ = 20.0;

            using (NativeMethods cylDLL = new NativeMethods())
            {
                distance = cylDLL.GetDistanceFromPt2Cyl(radius,
                            bottomX, bottomY, bottomZ,
                            topX, topY, topZ,
                            testptx, testpty, testptz
                            );
            }

            distance = GetDistFromPtToCylinder(radius,
                            bottomX, bottomY, bottomZ,
                            topX, topY, topZ,
                            testptx, testpty, testptz
                            );
            return distance;
        }

        // GET api/cylinders/5
        public Models.Cylinder Get(int id)
        {
            var cylinders = new Models.CylinderRepository();
            var cylinderList = cylinders.Retrieve();
            var Cylinder = cylinderList.FirstOrDefault(t => t.cylinderId == id);
            
            return Cylinder;
        }

        //// POST api/cylinders
        //public void Post([FromBody]string value)
        //{
        //}
        
        [HttpPost]
        public HttpResponseMessage Post([FromBody]Models.Cylinder cylJSON, [FromUri]double ptX, [FromUri]double ptY, [FromUri]double ptZ)
        {
            //HttpResponseMessage response = Request.CreateResponse(HttpStatusCode.Created, cylJSON);

            var dist = GetDistFromPtToCylinder(cylJSON.radius,
                cylJSON.bottomPt.X, cylJSON.bottomPt.Y, cylJSON.bottomPt.Z,
                cylJSON.topPt.X, cylJSON.topPt.Y, cylJSON.topPt.Z,
                ptX, ptY, ptZ);

            HttpResponseMessage response = Request.CreateResponse(HttpStatusCode.Created, dist);

            return response;
        }

        //// PUT api/cylinders/5
        //public void Put(int id, [FromBody]string value)
        //{
        //}

        // DELETE api/cylinder/5
        public void Delete(int id)
        {
        }

    }
}
