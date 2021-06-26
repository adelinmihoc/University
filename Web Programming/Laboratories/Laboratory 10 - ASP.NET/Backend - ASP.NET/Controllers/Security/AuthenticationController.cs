using Lab10.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Cors;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace Lab10.Controllers
{
    [EnableCors("_myAllowSpecificOrigins")]
    [Authorize]
    [Route("api/[controller]")]
    [ApiController]
    public class AuthenticationController : ControllerBase
    {
        private readonly UserContext _context;
        private readonly IJwtAuthenticationManager jwtAuthenticationManager;
        public AuthenticationController(IJwtAuthenticationManager jwtAuthenticationManager, UserContext context)
        {
            this.jwtAuthenticationManager = jwtAuthenticationManager;
            _context = context;
        }

        [AllowAnonymous]
        [HttpPost("authenticate")]
        public IActionResult Authenticate([FromBody] UserCred userCred) 
        {
            var user = _context.Users.Where(u => u.Username == userCred.Username).FirstOrDefault();
            if (user == null)
            {
                return NotFound();
            }
            if (user.Password != userCred.Password) 
            {
                return Unauthorized();
            }

            var token = jwtAuthenticationManager.Authenticate(userCred.Username);
            if (token == null)
            {
                return Unauthorized();
            }
            return Ok(token);
        }
    }
}
