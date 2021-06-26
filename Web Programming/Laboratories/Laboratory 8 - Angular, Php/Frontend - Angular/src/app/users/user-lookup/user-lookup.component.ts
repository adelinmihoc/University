import { Component, OnInit } from '@angular/core';
import {UserService} from '../shared/user.service';
import {User} from '../shared/user.model';

@Component({
  selector: 'app-user-lookup',
  templateUrl: './user-lookup.component.html',
  styleUrls: ['./user-lookup.component.css']
})
export class UserLookupComponent implements OnInit {
  users: User[];

  constructor(private userService: UserService) { }

  ngOnInit(): void {
  }

  // tslint:disable-next-line:typedef
  lookupUsers(name: string) {
    this.userService.lookupUsers(name).subscribe(users => this.users = users);
  }

}
