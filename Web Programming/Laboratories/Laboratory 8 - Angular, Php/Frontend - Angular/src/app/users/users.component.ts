import { Component, OnInit } from '@angular/core';
import {Router} from '@angular/router';
import {User} from './shared/user.model';
import {UserService} from './shared/user.service';

@Component({
  selector: 'app-users',
  templateUrl: './users.component.html',
  styleUrls: ['./users.component.css']
})
export class UsersComponent implements OnInit {

  constructor(private router: Router) { }

  ngOnInit(): void {
  }

}
