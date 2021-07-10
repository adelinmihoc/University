using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System;
using System.Text;
using System.Data.Common;
using MySqlConnector;
using asp_project.Models;


namespace asp_project.Controllers
{

    [Route("api/[controller]")]
    public class PrimaryController : ControllerBase
    {
        public PrimaryController(AppDb db)
        {
            Db = db;
        }
        public AppDb Db { get; }

        [HttpPost]
        [Route("/api/getAll")]
        public async Task<IActionResult> GetAll([FromBody]Entity body)
        {
            await Db.Connection.OpenAsync();
            var query = new DbUtil(Db);
            var result = await query.FindAllAsync2(body);
            return new OkObjectResult(result);
        }

        // [HttpGet]
        // [Route("/api/getOne")]
        // public async Task<IActionResult> GetOne([FromBody]Entity body)
        // {
        //     await Db.Connection.OpenAsync();
        //     var query = new DbUtil(Db);
        //     var result = await query.FindOneAsync(body);
        //     if (result == null) 
        //     {
        //         return new NotFoundResult();
        //     }
        //     return new OkObjectResult(result);
        // }

        [HttpPost]
        [Route("/api/add")]
        public async Task<IActionResult> Insert([FromBody]Entity body)
        {
            await Db.Connection.OpenAsync();
            var query = new DbUtil(Db);
            await query.InsertAsync(body);
            return new OkObjectResult(body);
        }

        [HttpPost]
        [Route("/api/update")]
        public async Task<IActionResult> Update([FromBody]Entity body)
        {
            await Db.Connection.OpenAsync();
            var query = new DbUtil(Db);
            await query.UpdateAsync(body);
            return new OkObjectResult(body);
        }

        [HttpPost]
        [Route("/api/delete")]
        public async Task<IActionResult> Delete([FromBody]Entity body)
        {
            await Db.Connection.OpenAsync();
            var query = new DbUtil(Db);
            await query.DeleteAsync(body);
            return new OkObjectResult(body);
        }

        [HttpPost]
        [Route("/api/authenticate")]
        public async Task<IActionResult> Authenticate([FromBody]Entity body)
        {
            await Db.Connection.OpenAsync();
            var query = new DbUtil(Db);
            var result = await query.AuthenticateAsync(body);
            if (result == null)
            {
                return new NotFoundResult();
            }
            return new OkObjectResult(result);
        }

        [HttpPost]
        [Route("/api/register")]
        public async Task<IActionResult> Register([FromBody]Entity body)
        {
            await Db.Connection.OpenAsync();
            var query = new DbUtil(Db);
            await query.RegisterAsync(body);
            return new OkObjectResult(body);
        }

    }
}