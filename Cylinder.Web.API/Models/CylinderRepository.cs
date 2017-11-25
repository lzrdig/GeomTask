using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Web;

namespace Cylinder.API.Models
{
    public class CylinderRepository
    {
        public List<Cylinder> CylinderList { get; set; }

        public List<Cylinder> Retrieve()
        {
            var filePath = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);
            filePath = Path.Combine(HttpContext.Current.Request.PhysicalApplicationPath, @"App_Data\cylinders.json");
            var json = System.IO.File.ReadAllText(filePath);
            var cylinders = JsonConvert.DeserializeObject<CylinderRepository>(json);

            return cylinders.CylinderList;
        }
    }
}