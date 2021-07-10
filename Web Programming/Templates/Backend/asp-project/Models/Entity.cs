using System;
using System.Threading.Tasks;
using MySqlConnector;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;


namespace asp_project.Models
{
    public class Entity
    {
        public string username { get; set; }
        public string password { get; set; }
        public int userid { get; set; }
        public string filename { get; set; }
        public int size { get; set; }
        public string filecontent { get; set; }
        public string word { get; set; }
        public int id { get; set; }
        public int apparitions { get; set; }


        public Entity()
        {
            
        }
    }
}
